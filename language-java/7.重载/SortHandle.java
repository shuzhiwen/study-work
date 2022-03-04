public interface SortHandle {
    public abstract void swap(int index);

    public abstract boolean outOfOrder(int index);

    public abstract int length();

    public abstract void setArray(Object array);
}
