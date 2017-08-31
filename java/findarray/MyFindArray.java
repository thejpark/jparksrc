package findarray;

public class MyFindArray implements FindArray
{

    public int findArray(int[] array, int[] subArray)
    {
        for (int i = 0; i < array.length; i++) {
            if (array.length - i  < subArray.length) {
                return -1;
            }

            int j;
            for (j = 0; j < subArray.length; j++) {
                if (array[i + j] != subArray[j]) {
                    break;
                }

            }

            if (j != 0 && j == subArray.length)
                return i;
        }

        return -1;

    }

}
