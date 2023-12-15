package edu.akron.algorithms.tone;

import org.jfugue.realtime.RealtimePlayer;
import org.jfugue.theory.Note;

import javax.sound.midi.MidiUnavailableException;

public class Tone {
    RealtimePlayer player;
    RealtimePlayer player2;
    int scale;
    int minVal;

    public Tone(int[] elements) throws MidiUnavailableException {
        //player.play("T220 m500/0.5 m525/0.5 m550/0.5 m575/0.5 m600/0.5 m625/0.5");
        //new Player().play(new ChordProgression("I IV vi V").eachChordAs("$_i $_i Ri $_i"), new Rhythm().addLayer("..X...X...X...XO"));
        player = new RealtimePlayer();
        player2 = new RealtimePlayer();
        minVal = Integer.MAX_VALUE;
        int maxVal = Integer.MIN_VALUE;
        for (final int element : elements) {
            if (element < minVal) minVal = element;
            if (element > maxVal) maxVal = element;
        }
        scale = maxVal - minVal;
    }

    public void compare(final int duration, final int value1, final int value2) throws InterruptedException {
        int tone = (value1 - minVal) * 75 / scale + 30;
        Note note = new Note(tone);
        tone = (value2 - minVal) * 75 / scale + 30;
        Note note2 = new Note(tone);
        player.startNote(note);
        player2.startNote(note2);
        Thread.sleep(duration);
        player.stopNote(note);
        player2.stopNote(note2);
    }

    public void play(final int duration, final int element) throws InterruptedException {
        final int tone = (element - minVal) * 75 / scale + 30;
        Note note = new Note(tone);
        player.startNote(note);
        Thread.sleep(duration);
        player.stopNote(note);
    }
}