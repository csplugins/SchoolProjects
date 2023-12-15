package edu.akron.algorithms.sorts;

import edu.akron.algorithms.visualize.Comparison;
import edu.akron.algorithms.visualize.SortStep;
import edu.akron.algorithms.visualize.Sorted;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class MergeSort implements GenericSort {
    public int[] _sort(final Queue<SortStep> q, int[] elements, int left, int right) {
        if (right - left < 1) return elements;
        final int middle = (left + right) >> 1;
        _sort(q, elements, left, middle);
        _sort(q, elements, middle + 1, right);
        int[] temp = new int[right - left + 1];
        int k = 0, l = left, m = middle + 1;
        while (l <= middle && m <= right) {
            final int finalL = l;
            final int finalM = m;
            q.offer(new SortStep(elements, new HashSet<Comparison>() {
                {
                    add(Comparison.basic(finalL));
                    add(Comparison.basic(finalM));
                }
            }));
            if (elements[l] < elements[m]) {
                temp[k++] = elements[l++];
                final int finalL1 = l;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.pick(finalL1 - 1));
                    }
                }));
            } else {
                temp[k++] = elements[m++];
                final int finalM1 = m;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.pick(finalM1 - 1));
                    }
                }));
            }
        }
        while (l <= middle) temp[k++] = elements[l++];
        while (m <= right) temp[k++] = elements[m++];
        for (int v = 0, i = left; i <= right; ++i, ++v) elements[i] = temp[v];
        return elements;
    }

    @Override
    public Sorted sort(int[] arr) {
        final Queue<SortStep> q = new LinkedList<>();
        final int[] arr2 = _sort(q, arr, 0, arr.length - 1);
        return new Sorted(arr2, q);
    }
}
