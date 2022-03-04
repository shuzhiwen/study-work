public class BubbleSorter {
    SortHandle handle;

    public BubbleSorter(SortHandle handle) {
        this.handle = handle;
    }

    public void doSort() {
        for (int nextToLast = handle.length() - 2; nextToLast >= 0; nextToLast--)
            for (int index = 0; index <= nextToLast; index++) {
                if (handle.outOfOrder(index)) {
                    handle.swap(index);
                }
            }
    }

    protected void setHandle(SortHandle handle) {
        this.handle = handle;
    }
}
