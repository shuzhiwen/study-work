public class Test {
    public static void main(String args[]) {
        IntBubbleHandle ib = new IntBubbleHandle();
        int a[] = { 1, 23, 4, 2, 5, 6, 3 };
        ib.setArray(a);
        ib.print();
        DoubleBubbleHandle db = new DoubleBubbleHandle();
        double b[] = { 1.2, 3.5, 2.7, 9.6, 4.6, 6.8 };
        db.setArray(b);
        db.print();

        BubbleSorter bs = new BubbleSorter(ib);
        bs.doSort();
        ib.print();
        bs.setHandle(db);
        bs.doSort();
        db.print();
    }
}