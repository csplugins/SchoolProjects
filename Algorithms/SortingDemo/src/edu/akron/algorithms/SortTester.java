package edu.akron.algorithms;

import edu.akron.algorithms.sorts.GenericSort;

public class SortTester {
    public static void main(final String[] params) {
        for (final Sort sort : Sort.values()) {
            final GenericSort s = sort.getSort();
            for (final Sample sample : Sample.values()) {
                final int[] a = sample.getData();
                final int[] validate = s.sort(a).array;
                int prev = validate[0];
                for (int i = 1; i < validate.length; ++i) {
                    if (validate[i] < prev) {
                        System.out.println(sort.toString() + " failed on " + sample.tag + ".");
                        break;
                    }
                    prev = validate[i];
                }
            }
        }
    }
}
