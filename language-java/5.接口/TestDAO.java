import java.util.*;

public class TestDAO {
    public static void main(String[] args) {
        DAO testDao = new DTest();

        // create 20 students;
        Student st[] = new Student[20];
        for (int i = 0; i < 20; i++) {
            Random ran = new Random();
            st[i] = new Student();
            st[i].setId("" + (i + 1));
            st[i].setScore(ran.nextInt(100));
            st[i].setName("stu" + (i + 1));
        }

        // add all 20 to database test;
        for (int i = 0; i < 20; i++) {
            testDao.add(st[i]);
        }

        // query 10-15 student data;
        List<Student> l1 = testDao.list(10, 5);
        System.out.println("query 10-15 student data");
        for (Student i : l1) {
            System.out
                    .println("query student, id=" + i.getId() + " name=" + i.getName() + " " + "score=" + i.getScore());
        }

        // query all student data;
        System.out.println("query all student data");
        List<Student> l2 = testDao.list();
        for (Student i : l2) {
            System.out
                    .println("query student, id=" + i.getId() + " name=" + i.getName() + " " + "score=" + i.getScore());
        }
    }
}
