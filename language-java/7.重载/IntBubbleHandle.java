public class IntBubbleHandle implements SortHandle {
    int[] array;

    public IntBubbleHandle() {
        array = new int[0];
    }

    public void swap(int index) {
        int tmp = array[index];
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
        for (int i : array) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public int length() {
        return array.length;
    }

    public void setArray(Object array) {
        this.array = (int[]) array;
    }
}