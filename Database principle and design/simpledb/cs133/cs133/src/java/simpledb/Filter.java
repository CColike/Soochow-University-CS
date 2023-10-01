package simpledb;

import java.util.*;

/**
 * Filter is an operator that implements a relational select.
 */
public class Filter extends Operator {

    private static final long serialVersionUID = 1L;
    
    Predicate p;
    DbIterator child;
    TupleDesc td;
    Iterator<Tuple> it;
    ArrayList<Tuple> tuples;

    /**
     * Constructor accepts a predicate to apply and a child operator to read
     * tuples to filter from.
     * 
     * @param p
     *            The predicate to filter tuples with
     * @param child
     *            The child operator
     */
    public Filter(Predicate p, DbIterator child) {
        // some code goes here
        this.p = p;
        this.child = child;
        this.td = child.getTupleDesc();
        this.tuples = new ArrayList<Tuple>();
    }

    public Predicate getPredicate() {
        // some code goes here
        return this.p;
//        return null;
    }

    public TupleDesc getTupleDesc() {
        // some code goes here
        return td;
//        return null;
    }

    public void open() throws DbException, NoSuchElementException,
            TransactionAbortedException {
        // some code goes here
    	child.open();
        Tuple next;
        while(child.hasNext()) {
            next = child.next();
            if(this.p.filter(next))
                tuples.add(next);
        }
        it = tuples.iterator();
        super.open();
    }

    public void close() {
        // some code goes here
        super.close();
        it = null;
    }

    public void rewind() throws DbException, TransactionAbortedException {
        // some code goes here
        it = tuples.iterator();
    }

    /**
     * The Filter operator iterates through the tuples from its child, 
     * applying the predicate to them and returning those that
     * pass the predicate (i.e. for which the Predicate.filter() returns true.)
     * This method returns the next tuple.
     * 
     * @return The next tuple that passes the filter, or null if there are no
     *         more tuples
     * @see Predicate#filter
     */
    protected Tuple fetchNext() throws NoSuchElementException,
            TransactionAbortedException, DbException {
        // some code goes here
        if(it != null && it.hasNext())
            return it.next();
        return null;
//        return null;
    }
    
    /**
     * See Operator.java for additional notes 
     */
    @Override
    public DbIterator[] getChildren() {
        // some code goes here
        return new DbIterator[] { this.child };
//        return null;
    }
    
    /**
     * See Operator.java for additional notes 
     */
    @Override
    public void setChildren(DbIterator[] children) {
        // some code goes here
        this.child = children[0];
    }

}
