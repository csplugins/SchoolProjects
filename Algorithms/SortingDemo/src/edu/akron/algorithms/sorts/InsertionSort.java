package edu.akron.algorithms.sorts;

import edu.akron.algorithms.visualize.Comparison;
import edu.akron.algorithms.visualize.SortStep;
import edu.akron.algorithms.visualize.Sorted;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class InsertionSort implements GenericSort {
    @Override
    public Sorted sort(int[] elements) {
        final Queue<SortStep> q = new LinkedList<>();
        for (int i = 1; i < elements.length; ++i) {
            int temp = elements[i];
            int j;
            for (j = i - 1; j >= 0 && temp < elements[j]; --j) {
                final int finalJ = j;
                final int finalI = i;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.special(finalI));
                        add(Comparison.basic(finalJ));
                        add(Comparison.basic(finalJ + 1));
                    }
                }));
                elements[j + 1] = elements[j];
            }
            elements[j + 1] = temp;
            final int finalJ = j;
            q.offer(new SortStep(elements, new HashSet<Comparison>() {
                {
                    add(Comparison.pick(finalJ + 1));
                }
            }));
        }
        return new Sorted(elements, q);
    }
}
