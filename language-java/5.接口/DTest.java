import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.*;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DTest implements DAO {
    public static final String driver = "com.mysql.jdbc.Driver";
    public static final String user = "root";
    public static final String dburl = "jdbc:mysql://localhost:3306";
    public static final String userpass = "123mutouren";

    private Connection con = null;
    private PreparedStatement cmd = null;

    public DTest() {
        conDatabase();
    }

    public void finalize() {
        if (con != null) {
            destroyCon();
        }
    }

    public void conDatabase() {
        try {
            Class.forName(driver);
            con = DriverManager.getConnection(dburl, user, userpass);
            System.out.println("conn is connencted");
        } catch (Exception e) {
            e.printStackTrace();
        }

        String cmdStr = "use test";
        try {
            cmd = con.prepareStatement(cmdStr);
            if (cmd.execute()) {
                System.out.println("use database test");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void add(Student st) {
        String cmdStr = "insert into student (id, name, score) values (?, ?, ?)";
        try {
            cmd = con.prepareStatement(cmdStr);
            cmd.setString(1, st.getId());
            cmd.setString(2, st.getName());
            cmd.setInt(3, st.getScore());
            cmd.executeUpdate();
            System.out.println(
                    "insert stu id=" + st.getId() + " " + "name=" + st.getName() + " " + "score=" + st.getScore());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void update(Student st) {
        String cmdStr = "update student set name=?, score=? where id=?";
        try {
            cmd = con.prepareStatement(cmdStr);
            cmd.setString(1, st.getName());
            cmd.setInt(2, st.getScore());
            cmd.setString(3, st.getId());
            cmd.executeUpdate();
            System.out.println(
                    "update stu id=" + st.getId() + " " + "name=" + st.getName() + " " + "score=" + st.getScore());
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Student> list() {
        return list(1, -1); // '-1' means all;
    }

    public List<Student> list(int start, int count) {
        List<Student> li = new ArrayList<>();
        String cmdStr = "select * from student";
        try {
            cmd = con.prepareStatement(cmdStr);
            ResultSet res = cmd.executeQuery();
            res.absolute(start);
            if (count == -1) {
                count = 999999;
            }

            for (int i = 0; i < count; i++) {
                Student st = new Student();
                st.setId(res.getString(1));
                st.setName(res.getString(2));
                st.setScore(res.getInt(3));
                li.add(st);
                if (!res.next()) {
                    break;
                }
            }
            return li;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void delete(String id) {
        String cmdStr = "delete from student where id=?";
        try {
            cmd = con.prepareStatement(cmdStr);
            cmd.setString(1, id);
            cmd.executeUpdate();
            System.out.println("delete student id =" + id);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public Student query(String id) {
        String cmdStr = "select * from student where id=?";
        try {
            cmd = con.prepareStatement(cmdStr);
            cmd.setString(1, id);
            ResultSet res = cmd.executeQuery();

            if (res.next()) {
                Student st = new Student();
                st.setId(res.getString(1));
                st.setName(res.getString(2));
                st.setScore(res.getInt(3));
                return st;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    public void destroyCon() {
        try {
            con.close();
            System.out.println("conn is destroyed");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}