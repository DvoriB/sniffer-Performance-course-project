

/*
 * print data in rows of 16 bytes: offset   hex   ascii
 *
 * 00000   47 45 54 20 2f 20 48 54  54 50 2f 31 2e 31 0d 0a   GET / HTTP/1.1..
 */
// void print_hex_ascii_line(const u_char *payload, int len, int offset)
// {

// 	int i;
// 	int gap;
// 	const u_char *ch;

// 	/* offset */
// 	printf("%05d   ", offset);

// 	/* hex */
// 	ch = payload;
// 	for (i = 0; i < len; i++)
// 	{
// 		printf("%02x ", *ch);
// 		ch++;
// 		/* print extra space after 8th byte for visual aid */
// 		if (i == 7)
// 			printf(" ");
// 	}
// 	/* print space to handle line less than 8 bytes */
// 	if (len < 8)
// 		printf(" ");

// 	/* fill hex gap with spaces if not full line */
// 	if (len < 16)
// 	{
// 		gap = 16 - len;
// 		for (i = 0; i < gap; i++)
// 		{
// 			printf("   ");
// 		}
// 	}
// 	printf("   ");

// 	/* ascii (if printable) */
// 	ch = payload;
// 	for (i = 0; i < len; i++)
// 	{
// 		if (isprint(*ch))
// 			printf("%c", *ch);
// 		else
// 			printf(".");
// 		ch++;
// 	}

// 	printf("\n");

// 	return;
// }

// /*
//  * print packet payload data (avoid printing binary data)
//  */
// void print_payload(const u_char *payload, int len)
// {

// 	int len_rem = len;
// 	int line_width = 16; /* number of bytes per line */
// 	int line_len;
// 	int offset = 0; /* zero-based offset counter */
// 	const u_char *ch = payload;

// 	if (len <= 0)
// 		return;

// 	/* data fits on one line */
// 	if (len <= line_width)
// 	{
// 		print_hex_ascii_line(ch, len, offset);
// 		return;
// 	}

// 	/* data spans multiple lines */
// 	for (;;)
// 	{
// 		/* compute current line length */
// 		line_len = line_width % len_rem;
// 		/* print line */
// 		print_hex_ascii_line(ch, line_len, offset);
// 		/* compute total remaining */
// 		len_rem = len_rem - line_len;
// 		/* shift pointer to remaining bytes to print */
// 		ch = ch + line_len;
// 		/* add offset */
// 		offset = offset + line_width;
// 		/* check if we have line width chars or less */
// 		if (len_rem <= line_width)
// 		{
// 			/* print last line and get out */
// 			print_hex_ascii_line(ch, len_rem, offset);
// 			break;
// 		}
// 	}

// 	return;
// }

// /*
//  * dissect/print packet
//  */
// void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
// {

// 	static int count = 1; /* packet counter */

// 	/* declare pointers to packet headers */
// 	const struct sniff_ethernet *ethernet; /* The ethernet header [1] */
// 	const struct sniff_ip *ip;			   /* The IP header */
// 	const struct sniff_tcp *tcp;		   /* The TCP header */
// 	const char *payload;				   /* Packet payload */

// 	int size_ip;
// 	int size_tcp;
// 	int size_payload;

// 	printf("\nPacket number %d:\n", count);
// 	count++;

// 	/* define ethernet header */
// 	ethernet = (struct sniff_ethernet *)(packet);

// 	/* define/compute ip header offset */
// 	ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
// 	size_ip = IP_HL(ip) * 4;
// 	if (size_ip < 20)
// 	{
// 		printf("   * Invalid IP header length: %u bytes\n", size_ip);
// 		return;
// 	}

// 	/* print source and destination IP addresses */
// 	printf("       From: %s\n", inet_ntoa(ip->ip_src));
// 	printf("         To: %s\n", inet_ntoa(ip->ip_dst));

// 	/* determine protocol */
// 	switch (ip->ip_p)
// 	{
// 	case IPPROTO_TCP:
// 		printf("   Protocol: TCP\n");
// 		break;
// 	case IPPROTO_UDP:
// 		printf("   Protocol: UDP\n");
// 		return;
// 	case IPPROTO_ICMP:
// 		printf("   Protocol: ICMP\n");
// 		return;
// 	case IPPROTO_IP:
// 		printf("   Protocol: IP\n");
// 		return;
// 	default:
// 		printf("   Protocol: unknown\n");
// 		return;
// 	}

// 	/*
// 	 *  OK, this packet is TCP.
// 	 */

// 	/* define/compute tcp header offset */
// 	tcp = (struct sniff_tcp *)(packet + SIZE_ETHERNET + size_ip);
// 	size_tcp = TH_OFF(tcp) * 4;
// 	if (size_tcp < 20)
// 	{
// 		printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
// 		return;
// 	}

// 	printf("   Src port: %d\n", ntohs(tcp->th_sport));
// 	printf("   Dst port: %d\n", ntohs(tcp->th_dport));

// 	/* define/compute tcp payload (segment) offset */
// 	payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);

// 	/* compute tcp payload (segment) size */
// 	size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

// 	/*
// 	 * Print payload data; it might be binary, so don't just
// 	 * treat it as a string.
// 	 */
// 	if (size_payload > 0)
// 	{
// 		printf("   Payload (%d bytes):\n", size_payload);
// 		print_payload(payload, size_payload);
// 	}

// 	return;
// }

// void linkedListWork(struct list *linkedList, char * ipAddress)
// {
//     struct listelement *newElement = (struct listelement *)malloc(sizeof(struct listelement));
//     newElement->val = ipAddress;
//     newElement->next = NULL;
//     if (linkedList->head == NULL)
//     {

//         linkedList->head = newElement;
//         return;
//     }
//     else
//     {
//         struct listelement *temporaryElement = linkedList->head;
//         while (1)
//         {
//             if (temporaryElement->next != NULL)
//             {
//                 temporaryElement = temporaryElement->next;
//                 if (temporaryElement->val == ipAddress)
//                 {
//                     // printf("EQUAL %lu and %lu", temporaryElement->val && ipAddress);
//                     return;
//                 }
//             }
//             else
//             {
//                 if (temporaryElement->val == ipAddress)
//                 {
//                     // printf("EQUAL %lu and %lu", temporaryElement->val && ipAddress);
//                     return;
//                 }

//                 temporaryElement->next = newElement;
//                 // printf("NEW %lu", newElement->val);
//                 return;
//             }
//         }
//     }
// }


// void printm(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
// {
// 	// add to data bace
// 	const struct sniff_ip *ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
// 	int value = *((int *)(hash, inet_ntoa(ip->ip_src)));
// 	printf("%s \n", inet_ntoa(ip->ip_src));
// 	// const char *ht_set(ht *table, const char *key, void *value);

// 	value += 1;

// 	ht_set(hash, inet_ntoa(ip->ip_src), (void *)value);
// 	if (counter == 0) // if --somethink
// 	{
// 		// send ip ,ip is long???
// 		// insert to the end of list becous i check if ip is exsite
// 		// linkedListWork(linkedList, (long)inet_ntoa(ip->ip_src));

// 		insertToList(linkedList, (long)inet_ntoa(ip->ip_src), listLock);

// 		// char *command = (char *)malloc(sizeof(char) * 100);
// 		// strcpy(command, "echo 213089345 | sudo -S iptables -I INPUT -d ");
// 		// strcat(command, inet_ntoa(ip->ip_src));
// 		// strcat(command, " -j DROP");
// 		// printf("%s\n", command);
// 		// system(command);
// 	}
// 	counter++;
// 	// int status = system("echo 213089345 | sudo -S iptables -I INPUT -s 142.251.37.46  -j DROP");
// }
// void blockIP(long ip){


// }

// void *threadFunction()
// {
// 	while (1)
// 	{
// 		long ip = pullFromList(linkedList, listLock);
// 		if (ip)
// 		{
// 			blockIP(ip);
// 		}
// 		else
// 		{
// 			// sleep on cv
// 		}
// 	}
// }
// =======

// enternet;
// cahr *ether_dhost     /* destination host address */
//     char *ether_dhost /* source host address */
//     char *ether_type; /* IP? ARP? RARP? etc */

// u_char ip_p; /* protocol */
// u_short ip_sum;
// ip : bigint srcip;
// bigit destinationip;
// tcp : u_short - ;
// srcport;
// destport;

// "INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
//                "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);"
//                "INSERT INTO PERSON VALUES(3, 'PAUL', 'JOBS', 24, 'SEATTLE', 9900.0);");
// >>>>>>> cc76f9ba8d665b15a6ace23250e73892ebe00b7e
