package iteration;

import java.util.List;
import java.util.Queue;

public interface Folder<T, U>
{
    public U fold(U u, Queue<T> list, Function2<T,U,U> function);
}
