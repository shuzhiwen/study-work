public class Test {
    public static void main(String args[]) {
        People p = new People();
        Student st = new Student();
        Teacher te = new Teacher();
        p.myJob(st);
        p.myJob(te);
    }
}