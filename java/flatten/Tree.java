package flatten;

public interface Tree<T> {

    Either<T, Triple<Tree<T>>> get();


    static final class Leaf<T> implements Tree<T> {

        public static <T> Leaf<T> leaf (T value) {
            return new Leaf<T>(value);
        }

        private final T t;

        private Leaf(T t) {
            this.t = t;
        }

        @Override
        public Either<T, Triple<Tree<T>>> get() {
            return Either.left(t);
        }
    }

    static final class Node<T> implements Tree<T> {
        public static <T> Tree<T> tree (Tree<T> left, Tree<T> middle, Tree<T> right) {
            return new Node<T>(left, middle, right);
        }

        private final Triple<Tree<T>> branches;

        private Node(Tree<T> left, Tree<T> middle, Tree<T> right) {
            this.branches = new Triple<Tree<T>>(left, middle, right);
        }

        @Override
        public Either<T, Triple<Tree<T>>> get() {
            return Either.right(branches);
        }
    }
}
