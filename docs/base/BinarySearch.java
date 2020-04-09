package VAlgorithm.docs.base;

public class BinarySearch {
    public static int binarySearch(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        int mid = 0;
        while(left <= right) {
            mid = left + ((right - left) >> 1);
            if (arr[mid] < target) {
                left = mid + 1;
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else {
                return mid;
            }
        }
        return -1;
    }

    public static int binarySearchLeft(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        int mid = 0;
        while(left <= right) {
            mid = left + ((right - left) >> 1);
            if (arr[mid] < target) {
                left = mid + 1;
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else {
                // 缩小右边界
                right = mid - 1;
            }
        }
        if (left >= arr.length || arr[left] != target) {
            return -1;
        }
        return left;
    }

    public static int binarySearchRight(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        int mid = 0;
        while(left <= right) {
            mid = left + ((right - left) >> 1);
            if (arr[mid] < target) {
                left = mid + 1;
            } else if (arr[mid] > target) {
                right = mid - 1;
            } else {
                // 缩小左边界
                left = mid + 1;
            }
        }
        if (right < 0 || arr[right] != target) {
            return -1;
        }
        return right;
    }

    public static void main(String[] args) {
        int[] arr = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        System.out.println(String.valueOf(binarySearch(arr, 0)));
        System.out.println(String.valueOf(binarySearch(arr, 2)));
        System.out.println(String.valueOf(binarySearch(arr, 9)));
        int[] arrA = new int[] { 1, 2, 3, 3, 3, 4, 5, 5, 9, 10 };
        System.out.println(String.valueOf(binarySearchLeft(arrA, 3)));
        System.out.println(String.valueOf(binarySearchLeft(arrA, 5)));
        System.out.println(String.valueOf(binarySearchRight(arrA, 3)));
        System.out.println(String.valueOf(binarySearchRight(arrA, 5)));
    }
}