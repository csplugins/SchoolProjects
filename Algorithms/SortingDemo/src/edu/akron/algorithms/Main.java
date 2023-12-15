package edu.akron.algorithms;

import edu.akron.algorithms.sorts.GenericSort;
import edu.akron.algorithms.tone.Tone;
import edu.akron.algorithms.visualize.Comparison;
import edu.akron.algorithms.visualize.SortStep;
import edu.akron.algorithms.visualize.Sorted;

import javax.sound.midi.MidiUnavailableException;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.util.*;
import java.util.Queue;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicReference;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Main implements Runnable {
    private static final int BAR_PADDING = 2;
    private final JFrame frame;
    private final JComboBox sort;
    private final JComboBox sample;
    private final JSlider slider;

    public Main() {
        frame = new JFrame();
        frame.getContentPane().setLayout(new BorderLayout());
        frame.setTitle("Sort Visualizer");
        frame.setLayout(new BorderLayout());
        final JPanel p1 = new JPanel();
        p1.setLayout(new FlowLayout());
        p1.add(new JLabel("Sort"));
        p1.add(sort = new JComboBox<>(Sort.values()));
        p1.add(new JLabel("Data"));
        p1.add(sample = new JComboBox<>(getSamples()));
        p1.add(new JLabel("Delay"));
        p1.add(slider = new JSlider(1, 1000, 25));
        final JButton b;
        p1.add(b = new JButton("Start"));

        frame.getContentPane().add(p1, BorderLayout.NORTH);
        final SortVisualizer v;
        frame.getContentPane().add(v = new SortVisualizer(), BorderLayout.CENTER);
        b.addActionListener(v);
    }

    public static void main(final String[] params) {
        final Runnable r = new Main();
        SwingUtilities.invokeLater(() -> {
            try {
                UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            } catch (final ClassNotFoundException | InstantiationException | IllegalAccessException | UnsupportedLookAndFeelException ignored) {
            }
            r.run();
        });
    }

    @Override
    public void run() {
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.pack();
        frame.setMinimumSize(frame.getSize());
        frame.setLocationRelativeTo(frame.getParent());
        frame.setVisible(true);
    }

    public class SortVisualizer extends JPanel implements ActionListener {
        private final int w, h;
        private final AtomicBoolean running = new AtomicBoolean(false);
        private final AtomicReference<SortStep> step = new AtomicReference<>();

        public SortVisualizer() {
            this(800, 500);
        }

        public SortVisualizer(final int w, final int h) {
            super();
            this.w = w;
            this.h = h;
            final Dimension d = new Dimension(w, h);
            setMinimumSize(d);
            setSize(d);
            setPreferredSize(d);
            setMaximumSize(d);
        }

        @Override
        public void paintComponent(final Graphics g) {
            g.setColor(Color.black);
            g.fillRect(0, 0, w, h);
            final SortStep step = this.step.get();
            if (step == null) {
                return;
            }
            final int[] data = step.arr;
            final int[] d2;
            Arrays.sort(d2 = data.clone());
            final int bar_width = (int) Math.floor(w / (double) data.length);
            for (int index = 0; index < data.length; ++index) {
                final int sx = index * bar_width + BAR_PADDING, ex = sx + bar_width - BAR_PADDING * 2;
                final int height = (int) Math.round(h * (data[index] / (double) d2[d2.length - 1]));
                g.setColor(Color.white);
                for (final Comparison c : step.comparisons) if (c.index == index) g.setColor(c.color);
                g.fillRect(sx, h - height, ex - sx, (int) Math.round(h * (data[index] / (double) d2[d2.length - 1])));
            }
        }

        @Override
        public void actionPerformed(final ActionEvent e) {
            final Sort s = (Sort) sort.getSelectedItem();
            final GenericSample s2 = (GenericSample) sample.getSelectedItem();
            if (!running.compareAndSet(false, true)) return;
            final Thread t = new Thread(() -> {
                final int[] data = s2.getData();
                final GenericSort sort = s.getSort();
                final int[] soda;
                final Sorted sorted = sort.sort(soda = Arrays.copyOf(data, Math.min(data.length, s.limit)));
                Tone tone = null;
                try {
                    tone = new Tone(soda);
                } catch (final MidiUnavailableException ignored) {
                }
                int swaps = 0, comparisons = 0, selects = 0;
                for (final SortStep step : sorted.steps) {
                    boolean hasbasic = false;
                    for (final Comparison c : step.comparisons) {
                        if (c.isBasic()) {
                            hasbasic = true;
                            break;
                        }
                    }
                    if (hasbasic) ++comparisons;
                    else if (step.comparisons.size() > 1) ++swaps;
                    else ++selects;
                }
                System.out.printf("%s: %s%n", Main.this.sort.getSelectedItem().toString(), Main.this.sample.getSelectedItem().toString());
                System.out.printf("Swaps: %d, Comparisons: %d, Selects: %d%n%n", swaps, comparisons, selects);
                final Queue<SortStep> q = new LinkedList<>(sorted.steps);
                final Set<Comparison> _comp = new HashSet<>();
                for (int i = 0; i < sorted.array.length; ++i) {
                    _comp.add(Comparison.done(i));
                    q.offer(new SortStep(sorted.array, new HashSet<>(_comp)));
                }
                for (final SortStep step : q) {
                    this.step.set(step);
                    Object[] ta = null;
                    int ta2 = -1;
                    if (step.comparisons.size() != 2) {
                        final HashSet<Comparison> set2 = new HashSet<>(step.comparisons);
                        set2.removeIf(comparison -> !comparison.isBasic());
                        if (set2.size() == 2) ta = set2.toArray();
                        else {
                            final HashSet<Comparison> set3 = new HashSet<>(step.comparisons);
                            set3.removeIf(c -> !c.isDone());
                            if (set3.size() > 0) {
                                int index = 0;
                                for (final Comparison c : set3) if (c.index > index) index = c.index;
                                ta2 = index;
                            }
                        }
                    } else ta = step.comparisons.toArray();
                    try {
                        SwingUtilities.invokeAndWait(this::repaint);
                    } catch (final InterruptedException | InvocationTargetException ignored) {
                    }
                    if (tone != null) {
                        try {
                            if (ta != null)
                                tone.compare(slider.getValue(), step.arr[((Comparison) ta[0]).index], step.arr[((Comparison) ta[1]).index]);
                            else if (ta2 >= 0) tone.play(slider.getValue(), sorted.array[ta2]);
                        } catch (final InterruptedException ex) {
                            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
                        }
                    }
                    try {
                        Thread.sleep(slider.getValue());
                    } catch (final InterruptedException ignored) {
                    }
                }
                running.set(false);
            });
            t.start();
        }
    }

    private static GenericSample[] getSamples() {
        final java.util.List<GenericSample> samples = new ArrayList<>(Arrays.asList(Sample.values()));
        try {
            Files.list(FileSystems.getDefault().getPath("samples")).filter(e -> e.getFileName().toString().endsWith(".sort")).forEach(path -> {
                try {
                    final java.util.List<String> lines = Files.readAllLines(path);
                    final Queue<Integer> q = new LinkedList<>();
                    final String name = lines.get(0);
                    for (int i = 1; i < lines.size(); ++i) {
                        try {
                            q.offer(Integer.parseInt(lines.get(i)));
                        } catch (final NumberFormatException ignored) {
                        }
                    }
                    final Integer[] data = new Integer[q.size()];
                    q.toArray(data);
                    final int[] rdata = new int[data.length];
                    for (int i = 0; i < data.length; ++i) rdata[i] = data[i];
                    samples.add(new GenericSample() {
                        @Override
                        public String getTag() {
                            return name;
                        }

                        @Override
                        public int[] getData() {
                            return rdata;
                        }

                        @Override
                        public String toString() {
                            return getTag();
                        }
                    });
                } catch (final IOException ignored) {
                }
            });
        } catch (final IOException ignored) {
        }
        final GenericSample[] arr = new GenericSample[samples.size()];
        for (int i = 0; i < arr.length; ++i) arr[i] = samples.get(i);
        return arr;
    }
}
