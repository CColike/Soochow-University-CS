package simpledb;
import java.util.*;
/**
 * Computes some aggregate over a set of IntFields.
 */
public class IntegerAggregator implements Aggregator {

    private static final long serialVersionUID = 1L;
    int gbfield, afield;
    Type gbfieldtype;
    Op what;
    HashMap<Field, Integer> data;
    HashMap<Field, Integer> count;
    /**
     * Aggregate constructor
     * 
     * @param gbfield
     *            the 0-based index of the group-by field in the tuple, or
     *            NO_GROUPING if there is no grouping
     * @param gbfieldtype
     *            the type of the group by field (e.g., Type.INT_TYPE), or null
     *            if there is no grouping
     * @param afield
     *            the 0-based index of the aggregate field in the tuple
     * @param what
     *            the aggregation operator
     */

    public IntegerAggregator(int gbfield, Type gbfieldtype, int afield, Op what) {
        this.gbfield = gbfield;
        this.afield = afield;
        this.gbfieldtype = gbfieldtype;
        this.what = what;
        data = new HashMap<Field, Integer>();
        count = new HashMap<Field, Integer>();
    }

    /**
     * Merge a new tuple into the aggregate, grouping as indicated in the
     * constructor. See Aggregator.java for more.
     * 
     * @param tup
     *            the Tuple containing an aggregate field and a group-by field
     */
    public void mergeTupleIntoGroup(Tuple tup) {
        Field groupbyfield;
        if(gbfield == -1)
            groupbyfield = null;
        else groupbyfield = tup.getField(gbfield);
        int aggregatefield = ((IntField) tup.getField(afield)).getValue();
        if(!data.containsKey(groupbyfield)) {
            data.put(groupbyfield,this.initialize());
            count.put(groupbyfield,0);
        }
        int currentvalue = data.get(groupbyfield);
        int currentcount = count.get(groupbyfield);
        int newvalue = currentvalue;
        if(this.what == Op.MIN) {
            if(currentvalue > aggregatefield)
                newvalue = aggregatefield;
        }
        else if(this.what == Op.MAX) {
            if(currentvalue < aggregatefield)
                newvalue = aggregatefield;
        }
        else {
            newvalue += aggregatefield;
        }
        data.put(groupbyfield,newvalue);
        int c = count.get(groupbyfield);
        count.put(groupbyfield, c+1);
    }

    public int initialize() {
        if(this.what == Op.MIN)
            return Integer.MAX_VALUE;
        if(this.what == Op.MAX) 
            return Integer.MIN_VALUE;
        return 0;
    }

    /**
     * Returns a DbIterator over group aggregate results.
     * 
     * @return a DbIterator whose tuples are the pair (groupVal, aggregateVal)
     *         if using group, or a single (aggregateVal) if no grouping. The
     *         aggregateVal is determined by the type of aggregate specified in
     *         the constructor.
     */
    public DbIterator iterator() {
        // some code goes here
        Iterator<Field> it = data.keySet().iterator();
        ArrayList<Tuple> tuples = new ArrayList<Tuple>();
        int i;
        TupleDesc td;
        Tuple tuple;
        Field field;
        if(gbfield==-1) {
            td = new TupleDesc(new Type[]{Type.INT_TYPE}, new String[] {"Aggregate"});
        }
        else
            td = new TupleDesc(new Type[]{gbfieldtype, Type.INT_TYPE}, new String[] {"Group By Field","Aggregate"});
        while(it.hasNext()) {
            field = it.next();
            tuple = new Tuple(td);
            int aggregate;
            if(what == Op.AVG) {
                aggregate = (int) (1.0*data.get(field)/count.get(field));
            }
            else if(what == Op.COUNT) {
                aggregate = count.get(field);
            }
            else
                aggregate = data.get(field);
            if(gbfield == -1)
                tuple.setField(0, new IntField(aggregate)); 
            else {
                tuple.setField(0, field);
                tuple.setField(1, new IntField(aggregate)); 
            }
            tuples.add(tuple);
        }

        return new TupleIterator(td,tuples);
    }

}