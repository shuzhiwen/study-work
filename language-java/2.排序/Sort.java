import java.util.*;

public class Sort {
    public static void main(String args[]) {
        Integer[] a = { 121, 31, 65, 165, 561, 56, 165, 156, 88, 275, 485 };

        Comparator cmp = new MyComparator();
        Arrays.sort(a, cmp);
        for (int i : a) {
            System.out.println(i + ' ');
        }
    }
}

class MyComparator implements Comparator<Integer> {
    public int compare(Integer o1, Integer o2) {
        return o2 - o1;
    }
}