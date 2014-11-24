/* subsystem name is "latency_tracker" */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM latency_tracker

#if !defined(_TRACE_LATENCY_TRACKER_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_LATENCY_TRACKER_H

#include <linux/tracepoint.h>
#include <linux/netdevice.h>

TRACE_EVENT(
	sched_latency,
	TP_PROTO(pid_t pid, u64 delay, unsigned int timeout),
	TP_ARGS(pid, delay, timeout),
	TP_STRUCT__entry(
		__field(int, pid)
		__field(u64, delay)
		__field(unsigned int, timeout)
	),
	TP_fast_assign(
		entry->pid = pid;
		entry->delay = delay;
		entry->timeout = timeout;
	),
	TP_printk("pid=%d, delay=%llu, timeout=%u", __entry->pid,
		__entry->delay, __entry->timeout)
   );

TRACE_EVENT(
	block_latency,
	TP_PROTO(dev_t dev, sector_t sector, u64 delay),
	TP_ARGS(dev, sector, delay),
	TP_STRUCT__entry(
		__field(u32, major)
		__field(u32, minor)
		__field(u64, sector)
		__field(u64, delay)
	),
	TP_fast_assign(
		entry->major = MAJOR(dev);
		entry->minor = MINOR(dev);
		entry->sector = sector;
		entry->delay = delay;
	),
	TP_printk("dev=(%u,%u), sector=%llu, delay=%llu",
		__entry->major, __entry->minor, __entry->sector,
		__entry->delay)
   );

TRACE_EVENT(
	net_latency,
	TP_PROTO(struct net_device *dev, u64 delay, unsigned int dropped,
		unsigned int timeout),
	TP_ARGS(dev, delay, dropped, timeout),
	TP_STRUCT__entry(
		__string(name, dev->name)
		__field(u64, delay)
		__field(unsigned int, dropped)
		__field(unsigned int, timeout)
	),
	TP_fast_assign(
		__assign_str(name, dev->name);
		entry->delay = delay;
		entry->dropped = dropped;
		entry->timeout = timeout;
	),
	TP_printk("iface=%s, delay=%llu, dropped=%u, timeout=%u",
		__get_str(name), __entry->delay, __entry->dropped,
		__entry->timeout)
   );

#endif /* _TRACE_LATENCY_TRACKER_H */

/* this part must be outside protection */
#include <trace/define_trace.h>
