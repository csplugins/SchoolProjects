package edu.akron.algorithms.sorts;

import edu.akron.algorithms.visualize.Comparison;
import edu.akron.algorithms.visualize.SortStep;
import edu.akron.algorithms.visualize.Sorted;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class BubbleSort implements GenericSort {
    @Override
    public Sorted sort(int[] elements) {
        final Queue<SortStep> q = new LinkedList<>();
        int n = elements.length;
        for (int i = 0; i < elements.length; ++i) {
            boolean did_swap = false;
            for (int j = 0; j < n - 1; ++j) {
                final int finalJ = j;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.basic(finalJ));
                        add(Comparison.basic(finalJ + 1));
                    }
                }));
                if (elements[j] > elements[j + 1]) {
                    did_swap = true;
                    int temp = elements[j];
                    elements[j] = elements[j + 1];
                    elements[j + 1] = temp;
                    q.offer(new SortStep(elements, new HashSet<Comparison>() {
                        {
                            add(Comparison.swap(finalJ));
                            add(Comparison.swap(finalJ + 1));
                        }
                    }));
                }
            }
            if (!did_swap) break;
            n--;
        }
        return new Sorted(elements, q);
    }
}
