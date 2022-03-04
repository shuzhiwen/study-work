public class AnyBubbleSorter extends BubbleSorter {
    int[] intdata;
    double[] doubledata;
    String[] stringdata;

    public AnyBubbleSorter(int a[]) {
        intdata = new int[a.length];
        System.arraycopy(a, 0, intdata, 0, a.length);
        length = a.length;
        sign = 1;
    }

    public AnyBubbleSorter(double a[]) {
        doubledata = new double[a.length];
        System.arraycopy(a, 0, doubledata, 0, a.length);
        length = a.length;
        sign = 2;
    }

    public AnyBubbleSorter(String a[]) {
        stringdata = new String[a.length];
        System.arraycopy(a, 0, stringdata, 0, a.length);
        length = a.length;
        sign = 3;
    }

    protected void swap(int index) {
        if (sign == 1) {
            int tmp = intdata[index];
            intdata[index] = intdata[index + 1];
            intdata[index + 1] = tmp;
        } else if (sign == 2) {
            double tmp = doubledata[index];
            doubledata[index] = doubledata[index + 1];
            doubledata[index + 1] = tmp;
        } else {
            String tmp = stringdata[index];
            stringdata[index] = stringdata[index + 1];
            stringdata[index + 1] = tmp;
        }
    }

    protected boolean outOfOrder(int index) {
        if (sign == 1) {
            return intdata[index] > intdata[index + 1] ? true : false;
        } else if (sign == 2) {
            return doubledata[index] > doubledata[index + 1] ? true : false;
        } else {
            return stringdata[index].compareTo(stringdata[index + 1]) > 0 ? true : false;
        }
    }

    public void print() {
        if (sign == 1) {
            for (int i : intdata) {
                System.out.print(i + " ");
            }
        } else if (sign == 2) {
            for (double i : doubledata) {
                System.out.print(i + " ");
            }
        } else {
            for (String i : stringdata) {
                System.out.print(i + " ");
            }
        }
        System.out.println();
    }

    public void setdata(int a[]) {
        intdata = new int[a.length];
        System.arraycopy(a, 0, intdata, 0, a.length);
        length = a.length;
        sign = 1;
    }

    public void setdata(double a[]) {
        doubledata = new double[a.length];
        System.arraycopy(a, 0, doubledata, 0, a.length);
        length = a.length;
        sign = 2;
    }

    public void setdata(String a[]) {
        stringdata = new String[a.length];
        System.arraycopy(a, 0, stringdata, 0, a.length);
        length = a.length;
        sign = 3;
    }
}