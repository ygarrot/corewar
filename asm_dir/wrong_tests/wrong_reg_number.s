.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r17, %:live, %1
		and r1, %0, r-10

live:	live %1
		zjmp %:live

