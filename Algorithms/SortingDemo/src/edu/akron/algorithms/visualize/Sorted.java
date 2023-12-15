package edu.akron.algorithms.visualize;

import java.util.Queue;

public class Sorted {
    public final int[] array;
    public final Queue<SortStep> steps;

    public Sorted(final int[] array, final Queue<SortStep> steps) {
        this.array = array;
        this.steps = steps;
    }
}
