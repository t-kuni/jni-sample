
class HelloWorld
{
    private native void print();
    public static void main(String[] args)
    {
        new HelloWorld().print();
        for (int i = 0; i < mdnNormal.length; i++) {
          System.out.println("mdnNormal[" + i + "]:" + mdnNormal[i]);
        }
    }
    static {
        System.loadLibrary("HelloWorld");
    }

    public static int test(int a, int b) {
      return a + b;
    }

    static private String[] mdnNormal;
}
