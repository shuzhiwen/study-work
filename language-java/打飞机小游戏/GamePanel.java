import javax.swing.JPanel;
import java.awt.Dimension;
import java.awt.Image;
import java.io.File;
import javax.imageio.ImageIO;
import java.awt.Graphics;
import java.awt.event.KeyListener;
import java.awt.event.KeyEvent;
import java.util.Random;
import java.util.Date;

public class GamePanel extends JPanel implements Runnable, KeyListener {
    private int width = 320;
    private int height = 480;
    private final int backStep = 10;

    private Image backScene0;
    private int back0Y;
    private Image backScene1;
    private int back1Y;

    private Player player = null;

    private Bullet[] bullets = null;
    private EnemyBullet[] enemybullets = null;
    private int numOfBullets = 15;
    private int numOfEnemyBullets = 100;
    private int shootInterval = 400;

    private EnemyPlane[] enemies = null;
    private int numOfEnemy = 8;

    private int r = 30;
    private Sound sound;

    private int score = 0;
    private ShowPanel gui;
    private int rebirthInterval = 0;

    public GamePanel(ShowPanel sp) {
        gui = sp;
        this.setPreferredSize(new Dimension(width, height));
        this.setVisible(true);
        // this.setFocusable(true);

        createBackScreen();
        createPlayer();
        createBullets();
        createEnemies();
        createEnemyBullets();

        sound = new Sound(player);
        sound.shootVoice();

        Thread t = new Thread(this);
        t.start();

        Thread t1 = new Thread() {
            public void run() {
                while (true) {
                    shootEnemyBullets();
                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        t1.start();

        this.addKeyListener(this);
    }

    public void run() {
        while (true) {
            try {
                repaint();
                moveBack();
                handleCollision();
                updatePlayer();
                updateEnemies();
                shootBullets();
                updateBullets();
                Thread.sleep(100);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public void createPlayer() {
        player = new Player();
        player.spawnPlane(140, 440);
        gui.updateLife(player.getLife());
    }

    public void updatePlayer() {
        if (player.isDead() && player.getLife() > 0) {
            if (rebirthInterval == 80) {
                player.spawnPlane(140, 440);
                rebirthInterval = 0;
                sound.shootVoice();
            } else {
                rebirthInterval++;
            }
        }
    }

    public void createEnemies() {
        enemies = new EnemyPlane[numOfEnemy];
        for (int i = 0; i < numOfEnemy; i++)
            enemies[i] = new EnemyPlane();
    }

    public void createBullets() {
        bullets = new Bullet[numOfBullets];
        for (int i = 0; i < numOfBullets; i++) {
            bullets[i] = new Bullet();
        }
    }

    public void createEnemyBullets() {
        enemybullets = new EnemyBullet[numOfEnemyBullets];
        for (int i = 0; i < numOfEnemyBullets; i++) {
            enemybullets[i] = new EnemyBullet();
        }
    }

    private void createBackScreen() {
        try {
            File fb0 = new File("images/map0.png");
            backScene0 = ImageIO.read(fb0);
            File fb1 = new File("images/map1.png");
            backScene1 = ImageIO.read(fb1);
        } catch (Exception e) {
            e.printStackTrace();
        }
        back1Y = 0;
        back0Y = -1 * height;
    }

    public boolean checkCollision(int x1, int y1, int x2, int y2) {
        int dstx = x2 - x1;
        int dsty = y2 - y1;

        return ((r * r) >= (dstx * dstx + dsty * dsty));
    }

    public void handleCollision() {
        int i, j;
        for (i = 0; i < numOfBullets; i++)
            for (j = 0; j < numOfEnemy; j++) {
                if (bullets[i].isInScreen() && enemies[j].isAlive()) {
                    if (checkCollision(bullets[i].getCenterX(), bullets[i].getCenterY(), enemies[j].getCenterX(),
                            enemies[j].getCenterY())) {
                        bullets[i].setOutScreen();
                        enemies[j].setDead();
                        score += 10;
                        gui.updateScore(score);
                        sound.explosionVoice();
                    }
                }
            }

        for (i = 0; i < numOfBullets; i++)
            for (j = 0; j < numOfEnemyBullets; j++) {
                if (bullets[i].isInScreen() && enemybullets[j].isInScreen()) {
                    if (checkCollision(bullets[i].getCenterX(), bullets[i].getCenterY(), enemybullets[j].getCenterX(),
                            enemybullets[j].getCenterY())) {
                        bullets[i].setOutScreen();
                        enemybullets[i].setOutScreen();
                        sound.explosionVoice();
                    }
                }
            }

        for (i = 0; i < numOfEnemy; i++) {
            if (enemies[i].isAlive() && player.isAlive()) {
                if (checkCollision(player.getCenterX(), player.getCenterY(), enemies[i].getCenterX(),
                        enemies[i].getCenterY())) {
                    enemies[i].setDead();
                    player.setDead();
                    gui.updateLife(player.getLife());
                    score += 10;
                    gui.updateScore(score);
                }
            }
        }

        for (i = 0; i < numOfEnemyBullets; i++) {
            if (enemybullets[i].isInScreen() && player.isAlive()) {
                if (checkCollision(player.getCenterX(), player.getCenterY(), enemybullets[i].getCenterX(),
                        enemybullets[i].getCenterY())) {
                    enemybullets[i].setOutScreen();
                    player.setDead();
                    gui.updateLife(player.getLife());
                    score += 10;
                    gui.updateScore(score);
                }
            }
        }
    }

    public void updateEnemies() {
        int i;

        if (player.isAlive()) {
            for (i = 0; i < numOfEnemy; i++) {
                if (enemies[i].isDead()) {
                    break;
                }
            }
            if (i < numOfEnemy) {
                enemies[i].spawnEnemy();
            }
        }

        for (i = 0; i < numOfEnemy; i++)
            enemies[i].update();
    }

    public void updateBullets() {
        for (int i = 0; i < numOfBullets; i++)
            bullets[i].update();
        for (int i = 0; i < numOfEnemyBullets; i++)
            enemybullets[i].update();
    }

    public void shootBullets() {
        if (player.isAlive()) {
            if (shootInterval == 2 * 200) {
                int i;
                for (i = 0; i < numOfBullets; i++) {
                    if (bullets[i].isOutScreen())
                        break;
                }
                bullets[i].shoot(player.getX(), player.getY());
                shootInterval = 0;
            } else {
                shootInterval += 200;
            }
        }
    }

    public void shootEnemyBullets() {
        Random rand = new Random();
        int probability;
        for (int enemyIndex = 0; enemyIndex < numOfEnemy; enemyIndex++) {
            probability = rand.nextInt(10);
            if (probability <= 1 && enemies[enemyIndex].isAlive() && enemies[enemyIndex].getCenterY() > 0) {
                int j;
                for (j = 0; j < numOfEnemyBullets; j++) {
                    if (enemybullets[j].isOutScreen())
                        break;
                }
                enemybullets[j].shoot(enemies[enemyIndex].getX(), enemies[enemyIndex].getY());
            }
        }
    }

    private void moveBack() {
        if (back0Y == height) {
            back0Y = -1 * height;
        } else {
            back0Y += backStep;
        }

        if (back1Y == height) {
            back1Y = -1 * height;
        } else {
            back1Y += backStep;
        }
    }

    public void paint(Graphics g) {
        g.drawImage(backScene0, 0, back0Y, this);
        g.drawImage(backScene1, 0, back1Y, this);

        player.drawPlane(g, this);

        for (int i = 0; i < numOfBullets; i++) {
            bullets[i].drawBullet(g, this);
        }

        for (int i = 0; i < numOfEnemyBullets; i++) {
            enemybullets[i].drawBullet(g, this);
        }

        for (int i = 0; i < numOfEnemy; i++) {
            enemies[i].drawEnemy(g, this);
        }

        if (player.getLife() == 0) {
            gui.drawGameover(g, this);
        }
    }

    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_UP) {
            player.upMove();
        } else if (key == KeyEvent.VK_DOWN) {
            player.downMove();
        } else if (key == KeyEvent.VK_LEFT) {
            player.leftMove();
        } else if (key == KeyEvent.VK_RIGHT) {
            player.rightMove();
        }
    }

    public void keyTyped(KeyEvent e) {
    }

    public void keyReleased(KeyEvent e) {
    }
}
