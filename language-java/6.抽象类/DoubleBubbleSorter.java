public class DoubleBubbleSorter extends BubbleSorter {
    double[] data;

    public DoubleBubbleSorter(double a[]) {
        data = new double[a.length];
        System.arraycopy(a, 0, data, 0, a.length);
        length = a.length;
    }

    protected void swap(int index) {
        double tmp = data[index];
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
        for (double i : data) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
}
