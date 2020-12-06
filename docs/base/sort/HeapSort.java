package VAlgorithm.docs.base.sort;

import java.util.Arrays;

public class HeapSort {
    public static void downAdjust(int[] array, int parrentIndex, int length) {
        // temp记录父节点
        int temp = array[parrentIndex];
        int childIndex = 2 * parrentIndex + 1;
        while (childIndex < length) {
            // 如果有右孩子，且右孩子大于左孩子的值，则定位到右孩子
            if (childIndex + 1 < length && array[childIndex + 1] > array[childIndex]) {
                childIndex++;
            }
            // 如果父节点大于任一孩子的值，直接跳出
            if (temp >= array[childIndex]) {
                break;
            }
            array[parrentIndex] = array[childIndex];
            parrentIndex = childIndex;
            childIndex = 2 * parrentIndex + 1;
        }
        array[parrentIndex] = temp;
    }

    public static void headpSort(int[] array) {
        // 1. 把无序数组构建成二叉堆
        for (int i = (array.length - 2) / 2; i >= 0; i--) {
            downAdjust(array, i, array.length);
        }
        // 2.循环删除堆顶元素，移到集合尾部，调节堆产生新的堆顶
        for (int i = array.length - 1; i > 0; i--) {
            // 最后一个元素和第一元素进行交换
            int temp = array[i];
            array[i] = array[0];
            array[0] = temp;
            // 下沉调整最大堆
            downAdjust(array, 0, i);
        }
    }

    public static void main(String[] args) {
        int[] arr = new int[] { 1, 3, 2, 6, 5, 7, 8, 9, 10, 0 };
        headpSort(arr);
        System.out.println(Arrays.toString(arr));
    }
}