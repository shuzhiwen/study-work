import java.awt.*;
import java.lang.*;
import javax.swing.*;
import java.awt.event.*;
import java.util.*;

class myThread extends JPanel implements Runnable, KeyListener {
    private int x = 0;
    private int y = 50;
    private JPanel jpanel1 = null;
    private String pst = null;
    static int socre = 0;
    static int sleepTime = 200;

    public myThread(JPanel jpanel1, String letter) {
        this.jpanel1 = jpanel1;
        this.pst = letter;
        x = (new Random()).nextInt(350);
        jpanel1.setFocusable(true);
        jpanel1.addKeyListener(this);
    }

    public void run() {
        JLabel show = new JLabel();
        show.setFont(new java.awt.Font("宋体", Font.PLAIN, 33));
        jpanel1.add(show);
        show.setText(pst);

        while (true) {
            repaint();
            show.setBounds(x, y, 33, 33);
            try {
                Thread.sleep(sleepTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            if (y >= 400) {
                break;
            } else {
                y += 10;
            }
        }

        show.setVisible(false);
        System.out.printf("结束线程%s%n", pst);
    }

    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_PAGE_UP) {
            sleepTime = 100;
        } else if (key == KeyEvent.VK_PAGE_DOWN) {
            sleepTime = 400;
        }
    }

    public void keyTyped(KeyEvent e) {
        char key = e.getKeyChar();

        if (pst.charAt(0) == key && y < 400) {
            socre += 10;
            y = 400;
        }
    }

    public void keyReleased(KeyEvent e) {
        sleepTime = 200;
    }
}