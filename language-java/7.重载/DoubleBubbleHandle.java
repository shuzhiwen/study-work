public class DoubleBubbleHandle implements SortHandle {
    double[] array;

    public DoubleBubbleHandle() {
        array = new double[0];
    }

    public void swap(int index) {
        double tmp = array[index];
        array[index] = array[index + 1];
        array[index + 1] = tmp;
    }

    public boolean outOfOrder(int index) {
        if (array[index] > array[index + 1]) {
            return true;
        } else {
            return false;
        }
    }

    public void print() {
        for (double i : array) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public int length() {
        return array.length;
    }

    public void setArray(Object array) {
        this.array = (double[]) array;
    }
}
