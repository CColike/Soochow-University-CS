package simpledb;
import java.util.*;

/**
 * Computes some aggregate over a set of StringFields.
 */
public class StringAggregator implements Aggregator {

    private static final long serialVersionUID = 1L;
    int gbfield, afield;
    Type gbfieldtype;
    Op what;
    HashMap<Field, Integer> count;
    /**
     * Aggregate constructor
     * @param gbfield the 0-based index of the group-by field in the tuple, or NO_GROUPING if there is no grouping
     * @param gbfieldtype the type of the group by field (e.g., Type.INT_TYPE), or null if there is no grouping
     * @param afield the 0-based index of the aggregate field in the tuple
     * @param what aggregation operator to use -- only supports COUNT
     * @throws IllegalArgumentException if what != COUNT
     */

    public StringAggregator(int gbfield, Type gbfieldtype, int afield, Op what) {
        this.gbfield = gbfield;
        this.afield = afield;
        this.gbfieldtype = gbfieldtype;
        this.what = what;
        count = new HashMap<Field, Integer>();
    }

    /**
     * Merge a new tuple into the aggregate, grouping as indicated in the constructor
     * @param tup the Tuple containing an aggregate field and a group-by field
     */
    public void mergeTupleIntoGroup(Tuple tup) {
        Field groupbyfield;
        if(gbfield == -1)
            groupbyfield = null;
        else groupbyfield = tup.getField(gbfield);
        if(!count.containsKey(groupbyfield))
            count.put(groupbyfield, 0);
        int c = count.get(groupbyfield);
        count.put(groupbyfield, c+1);
    }

    /**
     * Returns a DbIterator over group aggregate results.
     *
     * @return a DbIterator whose tuples are the pair (groupVal,
     *   aggregateVal) if using group, or a single (aggregateVal) if no
     *   grouping. The aggregateVal is determined by the type of
     *   aggregate specified in the constructor.
     */
    public DbIterator iterator() {
        Iterator<Field> it = count.keySet().iterator();
        ArrayList<Tuple> tuples = new ArrayList<Tuple>();
        int i;
        TupleDesc td;
        Tuple tuple;
        Field field;
        if(gbfield==-1) {
            td = new TupleDesc(new Type[]{Type.STRING_TYPE}, new String[] {"Aggregate"});
        }
        else
            td = new TupleDesc(new Type[]{gbfieldtype, Type.INT_TYPE}, new String[] {"Group By Field","Aggregate"});
        while(it.hasNext()) {
            field = it.next();
            tuple = new Tuple(td);
            int aggregate;      
            aggregate = count.get(field);
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