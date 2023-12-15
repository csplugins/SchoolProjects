package edu.akron.algorithms.sorts;

import edu.akron.algorithms.visualize.Comparison;
import edu.akron.algorithms.visualize.SortStep;
import edu.akron.algorithms.visualize.Sorted;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class QuickSort implements GenericSort {
    public int[] _sort(final Queue<SortStep> q, int[] elements, int left, int right) {
        int i = left, j = right;
        final int m;
        int a = elements[left], b = elements[left + ((right - left) >> 1)], c = elements[right];
        int pivot = ((a - b) * (b - c) > -1 ? left + ((right - left) >> 1) : ((a - b) * (a - c) < 1 ? left : right));
        int temp = elements[pivot];
        elements[pivot] = elements[left + ((right - left) >> 1)];
        elements[left + ((right - left) >> 1)] = temp;
        pivot = elements[m = left + ((right - left) >> 1)];
        while (i <= j) {
            while (elements[i] < pivot) {
                final int finalI = i;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.basic(finalI));
                        add(Comparison.special(m));
                    }
                }));
                ++i;
            }
            while (elements[j] > pivot) {
                final int finalJ = j;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.basic(finalJ));
                        add(Comparison.special(m));
                    }
                }));
                --j;
            }
            if (i <= j) {
                int swap = elements[i];
                elements[i] = elements[j];
                elements[j] = swap;
                final int finalJ1 = j;
                final int finalI1 = i;
                q.offer(new SortStep(elements, new HashSet<Comparison>() {
                    {
                        add(Comparison.swap(finalI1));
                        add(Comparison.swap(finalJ1));
                    }
                }));
                ++i;
                --j;
            }
        }
        if (left < j) _sort(q, elements, left, j);
        if (i < right) _sort(q, elements, i, right);
        return elements;
    }

    @Override
    public Sorted sort(int[] arr) {
        final Queue<SortStep> q = new LinkedList<>();
        final int[] arr2 = _sort(q, arr, 0, arr.length - 1);
        return new Sorted(arr2, q);
    }
}
