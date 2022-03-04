import java.util.*;

public class Student {
    String name;
    double height;
    double weight;
    private int score;

    public void setScore(int s) {
        score = s;
    }

    public int getScore() {
        return score;
    }

    public static void main(String args[]) {
        Student[] stuarray = new Student[10];
        Random random = new Random();

        for (int i = 0; i < 10; i++) {
            stuarray[i] = new Student();
            stuarray[i].name = "st" + String.valueOf(i + 1);
            stuarray[i].setScore(random.nextInt(101));
        }

        Comparator cmp = new MyComparator();
        Arrays.sort(stuarray, cmp);
        for (Student i : stuarray) {
            System.out.println(i.name + ": " + i.getScore());
        }
    }
}

class MyComparator implements Comparator<Student> {
    public int compare(Student o1, Student o2) {
        return o2.getScore() - o1.getScore();
    }
}