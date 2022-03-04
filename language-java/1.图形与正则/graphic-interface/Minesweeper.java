import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class ButtonListener implements ActionListener {
    JButton newButton;

    public ButtonListener(JButton b) {
        newButton = b;
    }

    public void actionPerformed(ActionEvent e) {
        newButton.setBackground(new Color(255, 255, 255));
    }
}

class ItemListener implements ActionListener {
    int size;
    JFrame newFrame;
    JLabel newLabel;

    public ItemListener(int n, JFrame f, JLabel l) {
        size = n;
        newFrame = f;
        newLabel = l;
    }

    public void actionPerformed(ActionEvent e) {
        JButton[] jb = new JButton[size * size];

        newLabel.removeAll();
        newLabel.setLayout(new GridLayout(size, size, 3, 3));

        for (int i = 0; i < size * size; i++) {
            jb[i] = new JButton("");
            jb[i].setBackground(new Color(100, 100, 100));
            jb[i].setPreferredSize(new Dimension(100, 40));

            ButtonListener bl = new ButtonListener(jb[i]);
            jb[i].addActionListener(bl);

            newLabel.add(jb[i]);
        }

        newFrame.pack();
    }
}

public class Minesweeper {
    private Minesweeper() {
        JFrame frame = new JFrame("Minesweeper");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel Label = new JLabel();
        Label.setBackground(new Color(255, 255, 150));
        Label.setPreferredSize(new Dimension(500, 500));

        madeMenuBar(frame, Label);

        frame.getContentPane().add(Label, BorderLayout.CENTER);
        frame.pack();
        frame.setVisible(true);
    }

    private void madeMenuBar(JFrame frame, JLabel Label) {
        JMenuBar menuBar;
        JMenu menu;
        JMenuItem menuItem;
        ItemListener il;

        menuBar = new JMenuBar();
        menuBar.setOpaque(true);
        menuBar.setBackground(new Color(0, 125, 200));
        menuBar.setPreferredSize(new Dimension(400, 30));

        menu = new JMenu("New Game");
        menuBar.add(menu);

        menuItem = new JMenuItem("5*5");
        il = new ItemListener(5, frame, Label);
        menuItem.addActionListener(il);
        menu.add(menuItem);

        menuItem = new JMenuItem("10*10");
        il = new ItemListener(10, frame, Label);
        menuItem.addActionListener(il);
        menu.add(menuItem);

        menuItem = new JMenuItem("20*20");
        il = new ItemListener(20, frame, Label);
        menuItem.addActionListener(il);
        menu.add(menuItem);

        menu = new JMenu("Hint");
        menuBar.add(menu);
        menu = new JMenu("Help");
        menuBar.add(menu);

        frame.setJMenuBar(menuBar);
    }

    public static void main(String[] args) {
        new Minesweeper();
    }
}