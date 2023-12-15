package edu.akron.algorithms;

import edu.akron.algorithms.sorts.*;

public enum Sort {
    QUICK("Quick Sort", new QuickSort(), Integer.MAX_VALUE),
    INSERT("Insertion Sort", new InsertionSort(), Integer.MAX_VALUE),
    MERGE("Merge Sort", new MergeSort(), Integer.MAX_VALUE),
    BUBBLE("Bubble Sort", new BubbleSort(), Integer.MAX_VALUE),
    RADIX("Radix Sort", new RadixSort(), Integer.MAX_VALUE);
    private final String name;
    private final GenericSort sort;
    public final int limit;

    Sort(final String name, final GenericSort sort, final int limit) {
        this.name = name;
        this.sort = sort;
        this.limit = limit;
    }

    public GenericSort getSort() {
        return sort;
    }

    @Override
    public String toString() {
        return name;
    }
}
