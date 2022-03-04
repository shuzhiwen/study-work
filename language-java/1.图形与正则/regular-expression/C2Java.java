import java.io.*;

public class C2Java {
    public static void main(String[] args) {
        try {
            FileReader fin = new FileReader("cl.c");
            FileWriter fout = new FileWriter("jl.java");
            BufferedReader br = new BufferedReader(fin);
            BufferedWriter bw = new BufferedWriter(fout);
            String line = "";
            String[] s = null;

            bw.write("public class jl {\n");
            while ((line = br.readLine()) != null) {
                s = line.split("[\\s\\t]+");
                bw.write("  private static final double " + s[1] + " = " + s[2] + "; // ");
                for (int i = 3; i < s.length; i++) {
                    bw.write(s[i]);
                }
                bw.write("\n");
            }
            bw.write("}");

            br.close();
            bw.close();
        } catch (Exception e) {
            System.out.println("操作失败！");
        }
    }
}