import java.io.*;
import java.util.HashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Email {
    public static Set<String> getEmailNumFromFile(String filePath) {
        Set<String> EmailSet = new HashSet<String>();

        try {
            File file = new File(filePath);

            if (file.isFile() && file.exists()) { // 判断文件是否存在
                InputStreamReader read = new InputStreamReader(new FileInputStream(file), "UTF-8");
                BufferedReader bufferedReader = new BufferedReader(read);
                String lineTxt = null;

                while ((lineTxt = bufferedReader.readLine()) != null) {
                    // 读取文件中的一行，将其中的电话号码添加到EmailSet中
                    CheckIfIsEmailNumber(lineTxt, EmailSet);
                }
                read.close();
            } else {
                System.out.println("找不到指定的文件");
            }
        } catch (Exception wrong) {
            System.out.println("读取文件内容出错");
            wrong.printStackTrace();
        }

        return EmailSet;
    }

    public static void CheckIfIsEmailNumber(String lineTxt, Set<String> EmailSet) {
        Pattern pattern = Pattern.compile("\\w+@\\w+.(com|edu.cn)");
        Matcher matcher = pattern.matcher(lineTxt);

        while (matcher.find()) {
            EmailSet.add(matcher.group());
        }
    }

    public static void main(String argv[]) {
        String filePath = "电子邮箱测试文件.txt";
        Set<String> EmailSet = getEmailNumFromFile(filePath);

        System.out.println("邮箱集合：" + EmailSet);
    }
}