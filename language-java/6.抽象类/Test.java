public class Test {
    public static void main(String args[]) {
        DoubleBubbleSorter a = new DoubleBubbleSorter(new double[] { 1.3, 5.9, 6.2, 5.7, 9.9 });
        a.doSort();
        a.print();
        IntBubbleSorter b = new IntBubbleSorter(new int[] { 1, 5, 6, 3, 9 });
        b.doSort();
        b.print();
    }
}