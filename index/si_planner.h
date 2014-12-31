#ifndef SI_PLANNER_H_
#define SI_PLANNER_H_

/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

typedef struct siplanner siplanner;
typedef struct siplan siplan;

struct siplanner {
	srrb branch;
	srrb compact;
};

/* plan */
#define SI_BRANCH        1
#define SI_COMPACT       2
#define SI_CHECKPOINT    4
#define SI_BACKUP        5

/* explain */
#define SI_ENONE         0
#define SI_ERETRY        1
#define SI_EINDEX_SIZE   2
#define SI_EINDEX_TTL    4
#define SI_EBRANCH_COUNT 3

struct siplan {
	int explain;
	int plan;
	/* branch:
	 *   a: index_size
	 *   b: ttl
	 *   c: ttl_wm
	 * compact:
	 *   a: branches
	 *   b:
	 *   c:
	 * checkpoint:
	 *   a: lsn
	 *   b:
	 *   c:
	 * backup:
	 *   a: bsn
	 *   b:
	 *   c:
	 */
	uint64_t a, b, c;
	sinode *node;
};

int si_planinit(siplan*);
int si_plannerinit(siplanner*);
int si_plannertrace(siplan*, srtrace*);
int si_plannerupdate(siplanner*, int, sinode*);
int si_plannerremove(siplanner*, int, sinode*);
int si_planner(siplanner*, siplan*);

#endif
