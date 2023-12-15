package edu.akron.algorithms.visualize;

import java.awt.Color;

public class Comparison {
    public final Color color;
    public final int index;

    public Comparison(final Color color, final int index) {
        this.color = color;
        this.index = index;
    }

    public boolean isBasic() {
        return color.equals(Color.red);
    }

    public boolean isDone() {
        return color.equals(Color.green);
    }

    public static Comparison basic(final int index) {
        return new Comparison(Color.red, index);
    }

    public static Comparison special(final int index) {
        return new Comparison(Color.green.darker(), index);
    }

    public static Comparison done(final int index) {
        return new Comparison(Color.green, index);
    }

    public static Comparison swap(final int index) {
        return new Comparison(Color.orange, index);
    }

    public static Comparison pick(final int index) {
        return new Comparison(Color.blue.brighter(), index);
    }

    @Override
    public String toString() {
        return String.format("%s - %s", color.toString(), index);
    }
}
