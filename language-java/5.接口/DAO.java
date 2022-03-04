import java.util.*;

public interface DAO {
    public void add(Student st);

    public void update(Student st);

    public void delete(String id);

    public Student query(String id);

    public List<Student> list();

    public List<Student> list(int start, int count);
}
