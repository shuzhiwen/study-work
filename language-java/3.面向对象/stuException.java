import java.util.*;
import java.lang.*;

public class stuException {
    String name;
    double height;
    double weight;
    private int score;

    public void setScore(int s) throws Exception {
        if (s > 100 || s < 0) {
            throw new Exception();
        } else {
            score = s;
        }
    }

    public int getScore() {
        return score;
    }

    public static void main(String args[]) {
        stuException stu = new stuException();
        boolean flag = true;

        while (flag) {
            try {
                Scanner data = new Scanner(System.in);
                stu.setScore(data.nextInt());
                data.close();
                flag = false;
                System.out.println("The student score is: " + stu.getScore());
            } catch (Exception e) {
                System.out.println("Your input is wrong, Please try again !");
            }
        }
    }
}
