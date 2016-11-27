import java.util.*;

/**
 * 出错的几个关键点：
 * （1）begin 和 end 的更新是middle+1
 *  (2) 退出的条件是begin > end ，相等的时候需要判断
 *  (3) 返回begin或者begin-1
 */
class BinarySearch {
    public static void main(String args[]) {
        /*
        List<float> list = new ArrayList();
        //(2.0, 8.0, 4.4, 2.8, 1.5, 9.1);
        list.add(2.0);
        list.add(8.0);
        list.add(4.4);
        list.add(2.8);
        list.add(1.5);
        list.add(9.1);
        */
        //System.out.println(args.length);
        if (args.length < 1)  {
            System.out.println("Usage: java BinarySearch niddle");
            System.exit(1);
        }
        double niddle = Double.parseDouble(args[0]);
        double[] items = {2.0, 8.0, 4.4, 2.8, 1.5, 9.1};
        //printArray(items);
        Arrays.sort(items);
        printArray(items);
        int idx = BinarySearch.search(items, niddle);
        System.out.println(idx);
        System.out.println(BinarySearch.searchLowBound(items, niddle));
        return;
    }
    public static int search(double[] list, double niddle) {
        if (null == list) {
            return -1;
        }
        int begin = 0;
        int end = list.length-1;
        int middle = 0;
        while (begin <= end) {
            middle = (begin + end) / 2;
            System.out.printf("%d\t%d\t%d\t%f\n", begin, end, middle, list[middle]);
            if (list[middle] == niddle) {
                return middle;
            } else if (list[middle] < niddle) {
                begin = middle + 1;
            } else if (list[middle] > niddle) {
                end = middle - 1;
            }
        }
        return -1;
    }

    public static int searchLowBound(double[] list, double niddle) {
        if (null == list) {
            return -1;
        }
        int begin = 0;
        int end = list.length-1;
        int middle = 0;
        int preBegin = 0;
        while (begin <= end) {
            middle = (begin + end) / 2;
            System.out.printf("Start in loop: %d\t%d\t%d\t%f\t%d\n", begin, end, middle, list[middle], preBegin);
            if (Math.abs(list[middle] - niddle) < 0.0000000001) {
                return middle;
            } else if (list[middle] < niddle) {
                preBegin = begin;
                begin = middle + 1;
            } else if (list[middle] > niddle) {
                end = middle - 1;
            }
            System.out.printf("End in loop: %d\t%d\t%d\t%f\t%d\n", begin, end, middle, list[middle], preBegin);
        }
        if (begin < list.length && list[begin] < niddle) {
            return begin;
        } else {
            return begin - 1;
        }
    }

    public static void printArray(double[] items) {
        for (int i=0; i < items.length; ++i) {
            System.out.printf("%d\t%f\n", i, items[i]);
        }
    }
}
