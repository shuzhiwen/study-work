import java.awt.*;
import java.lang.*;
import javax.swing.*;
import java.util.*;

public class game1 extends JFrame {
    JPanel contentPane = new JPanel();
    JPanel jpanel1 = new JPanel();

    public game1() {
        gameInit();
    }

    private void gameInit() {
        contentPane = (JPanel) getContentPane();
        setLayout(null);
        setSize(new Dimension(500, 500));
        setTitle("alphabet game");
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        jpanel1.setBounds(new Rectangle(20, 20, 400, 400));
        contentPane.add(jpanel1);
    }

    public static void main(String[] args) {
        game1 game = new game1();
        Random rand = new Random();
        Vector<Thread> t = new Vector<>();

        for (int i = 0; i < 10; i++) {
            String letter = String.valueOf((char) ((int) 'A' + rand.nextInt(26)));
            t.add(new Thread(new myThread(game.jpanel1, letter)));
            t.get(i).start();
            try {
                Thread.sleep(rand.nextInt(1000) + 200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        for (Thread t1 : t) {
            try {
                t1.join();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        JOptionPane.showMessageDialog(game.jpanel1, "你获得的分数为： " + myThread.socre);
    }
}