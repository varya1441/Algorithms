import org.apache.commons.lang.time.StopWatch;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

class Bus implements Comparable<Bus> {
    private final static SimpleDateFormat dt = new SimpleDateFormat("HH:mm", Locale.UK);
    private Date startTime;
    private Date reachTime;
    private String priority;

    Bus(String priority, Date startTime, Date reachTime) {
        this.startTime = startTime;
        this.reachTime = reachTime;
        this.priority = priority;
    }

    public Date getReachTime() {
        return reachTime;
    }

    public Date getStartTime() {
        return startTime;
    }


    public String getPriority() {
        return priority;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Bus bus = (Bus) o;

        if (startTime != null ? !startTime.equals(bus.startTime) : bus.startTime != null) return false;
        if (reachTime != null ? !reachTime.equals(bus.reachTime) : bus.reachTime != null) return false;
        return priority != null ? priority.equals(bus.priority) : bus.priority == null;
    }

    @Override
    public int hashCode() {
        int result = startTime != null ? startTime.hashCode() : 0;
        result = 31 * result + (reachTime != null ? reachTime.hashCode() : 0);
        result = 31 * result + (priority != null ? priority.hashCode() : 0);
        return result;
    }

    @Override
    public int compareTo(Bus o) {
        if (this.reachTime.equals(o.reachTime)) {
            if (this.startTime.equals(o.startTime)) {
                return o.priority.compareTo(this.priority);
            }
            return o.startTime.compareTo(startTime);
        } else
            return this.reachTime.compareTo(o.reachTime);
    }


    @Override
    public String toString() {
        return " " + dt.format(startTime) +
                " " + dt.format(reachTime);
    }
}


public class Main {
    private final static SimpleDateFormat dt = new SimpleDateFormat("HH:mm", Locale.UK);

    public static void main(String[] args) throws ParseException {
        StopWatch watch = new StopWatch();
        watch.start();

        Scanner sc = null;
        try {
            sc = new Scanner(new File("input.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        List<Bus> buses = new <Bus>ArrayList();
        while (sc.hasNext()) {
            buses.add(new Bus(sc.next(), dt.parse(sc.next()), dt.parse(sc.next())));
        }
        Collections.sort(buses);
        Map<String, List<Bus>> nBus = new <String, List<Bus>>LinkedHashMap();

        Date mTime = new Date(Long.MIN_VALUE);
        Calendar date = Calendar.getInstance();
        for (Bus b :
                buses) {
            date.setTime(b.getStartTime());
            date.add(Calendar.HOUR, 1);

            if ((date.getTime()).after(b.getReachTime())) {
                if (b.getStartTime().after(mTime)) {
                    mTime = b.getStartTime();
                    String key = b.getPriority();
                    if (!nBus.containsKey(key)) {
                        nBus.put(key, new ArrayList<Bus>(Arrays.asList(b)));

                    } else {
                        nBus.get(key).add(b);
                    }
                }
            }
        }
        try (FileWriter fileWriter = new FileWriter("output.txt")) {

            nBus.forEach((priority, pBuses) -> {
                pBuses.stream().forEach(bus -> {
                    try {
                        fileWriter.write(priority + bus + '\n');
                    } catch (IOException e) {
                        System.err.format("IOException: %s%n", e);
                    }
                });
                try {
                    fileWriter.write("\n");
                } catch (IOException e) {
                    System.err.format("IOException: %s%n", e);
                }
            });
        } catch (IOException e) {
            System.err.format("IOException: %s%n", e);
        }
        watch.stop();
        System.out.println("Time Elapsed: " + watch.getTime());
    }
}
