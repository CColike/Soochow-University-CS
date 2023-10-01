package simpledb;

import java.util.*;

/**
 * The Join operator implements the relational join operation.
 */
public class Join extends Operator {

    private static final long serialVersionUID = 1L;
    JoinPredicate p;
    DbIterator child1;
    DbIterator child2;
    TupleDesc td1;
    TupleDesc td2;
    TupleDesc td;
    Iterator<Tuple> it;
    ArrayList<Tuple> tuples;

    /**
     * Constructor. Accepts two children to join and the predicate to join them
     * on
     * 
     * @param p
     *            The predicate to use to join the children
     * @param child1
     *            Iterator for the left(outer) relation to join
     * @param child2
     *            Iterator for the right(inner) relation to join
     */
    public Join(JoinPredicate p, DbIterator child1, DbIterator child2) {
        // some code goes here
        this.p = p;
        this.child1 = child1;
        this.child2 = child2;
        this.td1 = this.child1.getTupleDesc();
        this.td2 = this.child2.getTupleDesc();
        td = TupleDesc.merge(this.td1,this.td2);
        this.tuples = new ArrayList<Tuple>();
    }

    public JoinPredicate getJoinPredicate() {
        // some code goes here
        return this.p;
//        return null;
    }

    /**
     * @return
     *       the field name of join field1. Should be quantified by
     *       alias or table name. Can be taken from the appropriate child's TupleDesc.
     * */
    public String getJoinField1Name() {
        // some code goes here
        return td1.getFieldName(p.getField1());
//        return null;
    }

    /**
     * @return
     *       the field name of join field2. Should be quantified by
     *       alias or table name. Can be taken from the appropriate child's TupleDesc.
     * */
    public String getJoinField2Name() {
        // some code goes here
        return td2.getFieldName(p.getField2());
//        return null;
    }

    /**
     * Should return a TupleDesc that represents the schema for the joined tuples. 
     *@see simpledb.TupleDesc#merge(TupleDesc, TupleDesc) for possible
     *      implementation logic.
     */
    public TupleDesc getTupleDesc() {
        // some code goes here
        return this.td;
//        return null;
    }

    public void open() throws DbException, NoSuchElementException,
            TransactionAbortedException {
        // some code goes here
        child1.open();
        child2.open();

        Tuple next,next1,next2;
        int i,j,l1 = td1.numFields(), l2 = td2.numFields();
        while(child1.hasNext()) {
            next1 = child1.next();
            child2.rewind();
            while(child2.hasNext()) {
                next2 = child2.next();
                if(this.p.filter(next1,next2)) {
                    next = new Tuple(td);
                    for(i=0;i<l1;i++) 
                        next.setField(i,next1.getField(i));
                    for(j=0;j<l2;j++) 
                        next.setField(l1 + j,next2.getField(j));
                    tuples.add(next);
                }
        
            }
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
     * Returns the next tuple generated by the join, or null if there are no
     * more tuples. Logically, this is the next tuple in r1 cross r2 that
     * satisfies the join predicate. There are many possible implementations;
     * the simplest is a nested loops join.
     * <p>
     * Note that the tuples returned from this particular implementation of Join
     * are simply the concatenation of joining tuples from the left and right
     * relation. Therefore, if an equality predicate is used there will be two
     * copies of the join attribute in the results. (Removing such duplicate
     * columns can be done with an additional projection operator later on if needed.)
     * <p>
     * For example, if one tuple is {1,2,3} and the other tuple is {1,5,6},
     * joined on equality of the first column, then this returns {1,2,3,1,5,6}.
     * 
     * @return The next matching tuple.
     * @see JoinPredicate#filter
     */
    protected Tuple fetchNext() throws TransactionAbortedException, DbException {
        // some code goes here
        if(it != null && it.hasNext())
            return it.next();
        return null;
    }

    /**
     * See Operator.java for additional notes
     */
    @Override
    public DbIterator[] getChildren() {
        // some code goes here
        return new DbIterator[]{ this.child1, this.child2 };
//        return null;
    }

    /**
     * See Operator.java for additional notes
     */
    @Override
    public void setChildren(DbIterator[] children) {
        // some code goes here
        child1 = children[0];
        child2 = children[1];
    }

}
