import java.io.*;
import java.util.HashSet;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Phone {
    public static Set<String> getPhoneNumFromFile(String filePath) {
        Set<String> phoneSet = new HashSet<String>();

        try {
            File file = new File(filePath);

            if (file.isFile() && file.exists()) { // 判断文件是否存在
                InputStreamReader read = new InputStreamReader(new FileInputStream(file), "UTF-8");
                BufferedReader bufferedReader = new BufferedReader(read);
                String lineTxt = null;

                while ((lineTxt = bufferedReader.readLine()) != null) {
                    // 读取文件中的一行，将其中的电话号码添加到phoneSet中
                    CheckIfIsPhoneNumber(lineTxt, phoneSet);
                }
                read.close();
            } else {
                System.out.println("找不到指定的文件");
            }
        } catch (Exception wrong) {
            System.out.println("读取文件内容出错");
            wrong.printStackTrace();
        }

        return phoneSet;
    }

    public static void CheckIfIsPhoneNumber(String lineTxt, Set<String> phoneSet) {
        Pattern pattern = Pattern.compile("[0-9]{11}");
        Matcher matcher = pattern.matcher(lineTxt);

        while (matcher.find()) {
            phoneSet.add(matcher.group());
        }
    }

    public static void main(String argv[]) {
        String filePath = "手机号码测试文件.txt";
        Set<String> phoneSet = getPhoneNumFromFile(filePath);

        System.out.println("电话集合：" + phoneSet);
    }
}