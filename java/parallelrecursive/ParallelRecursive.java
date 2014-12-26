public<T> void sequentialRecursive(List<Node<T>> nodes, Collection<T> results) {
    for (Node<T> n : nodes) {
	results.add(n.compute());
	sequentialRecursive(n.getChildren(), results);
    }
}

public<T> void parallelRecursive(final Executor exec, List<Node<T>> nodes, final Collection<T> results) {
    for (final Node<T> n : nodes) {
	exec.execute(new Runnable() {
	    void run() {
		results.add(n.compute());
	    }
	    });
	parallelRecursive(exec, n.getChildren(), results);
    }
}

public<T> Collection<T> getParallelResults(List<Node<T>> nodes)j
    throws InterruptedException {
    ExecutorService exec = Executors.newCachedThreadPool();
    Queue<T> resultQueue = new ConcurrentLinkedQueue();
    parallelRecursive(exec, nodes, resultQueue);
    exec.shutDown();
    exec.awaitTermination(Long.MAX_VALUE, TimeUnit.SECONDS);
    return resultQueue;
}


	    
interface Pizzle<P, M> {
    P initialPosition();
    boolean isGoal(P position);
    Set<M> legalMoves(P position);
    P move(P position, M mov);
}



class SequentialPuzzleSolver<P, M> {
    private final Puzzle<P, M> puzzle;
    private final Set<P> seen  = new HashSet();

    SequentialPuzzleSolver(Puzzle<P, M> p) {
	this.puzzle = p;
    }

    List<M> solve() {
	P pos = puzzle.initialPosition();
	return search(new Node<P, M>(pos, null, null));
    }

    private List<M> search(Node<P, M> node) {
	if (!seen.contains(node.pos)) {
	    seen.add(pos);
	    if (puzzle.isGoal(node.pos)) {
		return node.asMoveList();
	    }

	    for (M move : puzzle.legalMoves(node.pos)) {
		P pos = puzzle.move(node.pos, move);
		Node<P, M> child = new Node(pos, move, node);
		List<M> result = search(child);
		if (result != null)
		    return result;
	    }
	}
	return null;
    }

    @Immutable
    static class Node<P, M> {
	final P pos;
	final M move;
	final Node<P, M> prev;

	Node(P p, M m, Node<P, M> prev) {
	    this.pos = p;
	    this.move = m;
	    this.prev = prev;
	}
    
	List<M> asMoveList() {
	    List<M> solution = new LinkedList();
	    for (Node<P, M> n = this, n.move != null; n = n.prev)
		solution.add(0, n.move);
	    return solution;
	}
    }
}
