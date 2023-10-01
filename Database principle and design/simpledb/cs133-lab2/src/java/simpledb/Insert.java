package simpledb;

/**
 * Inserts tuples read from the child operator into the tableid specified in the
 * constructor
 */
public class Insert extends Operator {

    private static final long serialVersionUID = 1L;

    /**
     * Constructor.
     * 
     * @param t
     *            The transaction running the insert.
     * @param child
     *            The child operator from which to read tuples to be inserted.
     * @param tableid
     *            The table in which to insert tuples.
     * @throws DbException
     *             if TupleDesc of child differs from table into which we are to
     *             insert.
     */
    public Insert(TransactionId t,DbIterator child, int tableid)
            throws DbException {
        // some code goes here
    }

    public TupleDesc getTupleDesc() {
        // some code goes here
        return null;
    }

    public void open() throws DbException, TransactionAbortedException {
        // some code goes here
    }

    public void close() {
        // some code goes here
    }

    /**
     * You can just close and then open the child
     */
    public void rewind() throws DbException, TransactionAbortedException {
        // some code goes here
    }

    /**
     * Inserts tuples read from child into the relation with the tableid specified by the
     * constructor. It returns a one field tuple containing the number of
     * inserted records (even if there are 0!). 
     * Insertions should be passed through BufferPool.insertTuple() with the 
     * TransactionId from the constructor. An instance of BufferPool is available via 
     * Database.getBufferPool(). Note that insert DOES NOT need to check to see if 
     * a particular tuple is a duplicate before inserting it.
     *
     * This operator should keep track if its fetchNext() has already been called, 
     * returning null if called multiple times.
     * 
     * @return A 1-field tuple containing the number of inserted records, or
     *         null if called more than once.
     * @see Database#getBufferPool
     * @see BufferPool#insertTuple
     */
    protected Tuple fetchNext() throws TransactionAbortedException, DbException {
        // some code goes here
        return null;
    }

    @Override
    public DbIterator[] getChildren() {
        // some code goes here
        return null;
    }

    @Override
    public void setChildren(DbIterator[] children) {
        // some code goes here
    }
}
