public class IntBubbleSorter extends BubbleSorter {
    int[] data;

    public IntBubbleSorter(int a[]) {
        data = new int[a.length];
        System.arraycopy(a, 0, data, 0, a.length);
        length = a.length;
    }

    protected void swap(int index) {
        int tmp = data[index];
        data[index] = data[index + 1];
        data[index + 1] = tmp;
    }

    protected boolean outOfOrder(int index) {
        if (data[index] > data[index + 1]) {
            return true;
        } else {
            return false;
        }
    }

    public void print() {
        for (int i : data) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}