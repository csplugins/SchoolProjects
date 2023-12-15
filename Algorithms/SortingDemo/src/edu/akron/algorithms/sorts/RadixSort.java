package edu.akron.algorithms.sorts;

import edu.akron.algorithms.visualize.Comparison;
import edu.akron.algorithms.visualize.SortStep;
import edu.akron.algorithms.visualize.Sorted;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;

public class RadixSort implements GenericSort {
    @Override
    public Sorted sort(int[] elements) {
        final Queue<SortStep> q = new LinkedList<>();
        Queue<Integer> main_queue = new LinkedList<>();
        if (elements.length <= 0) return new Sorted(elements, q);
        int largest = elements[0];
        final int[] index = {0};
        for (int element : elements) {
            main_queue.add(element);
            largest = largest < element ? element : largest;
            q.offer(new SortStep(elements, new HashSet<Comparison>() {
                {
                    add(Comparison.basic(index[0]++));
                }
            }));
        }
        int digits = 0;
        do {
            largest /= 10;
            ++digits;
        } while (largest != 0);
        @SuppressWarnings("unchecked")
        Queue<Integer>[] buckets = new Queue[10];
        for (int i = 0; i < 10; ++i) {
            buckets[i] = new LinkedList<>();
        }
        //TODO: add more radix comparisons
        int den = 1;
        for (int i = 0; i < digits; ++i) {
            while (main_queue.size() > 0) {
                int temp = main_queue.remove();
                buckets[(temp / den) % 10].add(temp);
            }
            for (int j = 0; j < 10; ++j) {
                while (buckets[j].size() > 0) {
                    main_queue.add(buckets[j].remove());
                }
            }
            den *= 10;
        }
        int i = 0;
        while (main_queue.size() > 0) {
            elements[i] = main_queue.remove();
            i++;
        }
        return new Sorted(elements, q);
    }
}
