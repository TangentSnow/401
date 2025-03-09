module PageRank = Map.Make(String)
module PageSet = Set.Make(String)

(*
    Homework 2: Implementing Pagerank
    cc: Akshar Patel (akshar20@uab.edu), Michael Gathara (mikegtr@uab.edu)

    Pagerank is a popular graph algorithm used for information retrieval and 
    was popularized by Google as the core algorithm powering the Google 
    search engine. We will discuss the pagerank algorithm in lab, but we 
    encourage you to learn more about it using the internet. Here, you will 
    implement several functions that implement the PageRank algorithm in OCaml.

    Hints:

    - You can assume that no graph will include self-links and that each page
      will link to at least one other page.

    - You can assume that there will be no repeat links in the graph

    - You can define your own functions if you want to break up complicated 
      function definitions

    - Do not change the core (the ones we give here) function signatures

    Submission:
    - On Canvas: Required: This file, ICF, Report (pdf)
    - On Github: Required: This file  
                 Optional: ICF & Report 
*)


(*
   numPages: Computes the total number of pages present in the graph.
   For example, for the graph [("n0", "n1"); ("n1", "n2")], the result is 3
   since the pages are "n0", "n1", and "n2".
   
   Input: graph as a list of (string * string) tuples (each representing a
   link from one page to another)
   Output: int representing the number of unique pages in the graph
*)

(* A helper function that takes a tuple (representing a link between two pages)  
and adds them to acc (a set) that holds the set of unique pages. *)
let add_pages acc (p1, p2) =
  PageSet.add p1 (PageSet.add p2 acc) 

let numPages graph =
    (* raise (Failure "TODO: implement numPages") *)
    let unique_PageSet = List.fold_left add_pages PageSet.empty graph in  (*Iterate over the list and apply add_page to the list using left fodl, at the end the set will contain unique pages*)
    PageSet.cardinal unique_PageSet (*Returns the number of total elements in the set*)

(*
   numLinks: Computes the number of outbound links from the given page.
   For example, given the graph [("n0", "n1"); ("n1", "n0"); ("n0", "n2")]
   and the page "n0", the function should return 2 because "n0" links to
   "n1" and "n2".
   
   Input: 
     - graph: a list of (string * string) representing the graph's links
     - page: a string representing the page whose outbound links are to be
       counted
   Output:
     - int representing the number of links emanating from the given page
*)
let numLinks graph page =
    (* raise (Failure "TODO: implement numLinks") *)
    let outbound_links = List.filter (fun (p1, _) -> p1 = page) graph in  (*extract links from the graph where the first element in the tuples match the given page*)
    List.length outbound_links  (*Return the number of elements in the list*)

(*
   getBacklinks: Computes the set of pages that link to the given page.
   For example, in the graph [("n0", "n1"); ("n1", "n2"); ("n0", "n2")] and
   the page "n2", the function should return a set containing "n0" and "n1".
   
   Input:
     - graph: a list of (string * string) representing the graph's links
     - page: a string representing the page for which backlinks are sought
   Output:
     - PageSet.t (set of strings) representing all pages that link to
       the given page
*)
let getBacklinks graph page =
    (* raise (Failure "TODO: implement getBacklinks") *)
    let back_links = List.filter (fun (_, p2) -> p2 = page) graph in (* Same as the last function but applied on the second element in the tuple to (the destination) that matches the given page *)
    let source_pages = List.map (fun (p1, _) -> p1) back_links in   (*Extract the first element from each tuple (the source page)*)
    List.fold_left (fun set src -> PageSet.add src set) PageSet.empty source_pages  (*Create a set of all the source pages that link to the given page*)

(*
   initPageRank: Generates the initial PageRank for the given graph.
   Each page is assigned an equal rank of 1/N, where N is the total number
   of pages, so that the sum of all page ranks is 1.
   
   Input: graph as a list of (string * string) representing the graph
   Output: a PageRank map (string -> float) with each page mapped to its
   initial rank (1/N)
*)
let initPageRank graph =
    (* raise (Failure "TODO: implement initPageRank") *)
    let n = numPages graph in (* Using the previously implemented numPages to get the unique number of pages in the graph *)
    let initial_rank = 1.0 /. float_of_int n in (* Initial rank for each page *)
    let unique_pages_set = List.fold_left add_pages PageSet.empty graph in  (*Re-compute unique pages, because we need the set of unique pages to create a map and not an int representing the number of unique pages (aka we cannot use numPages here, we can still use add_pages)*)
    PageSet.fold (fun page map -> PageRank.add page initial_rank map) unique_pages_set PageRank.empty (*Create a map, that adds each page with it's initial rank*)



(*
   stepPageRank: Performs one iteration step of the PageRank algorithm
   on the graph, updating every page with a new weight.
   The new rank for each page is calculated using the formula:
   
       NewRank(page) = (1 - d) / N + d * S

   where:
     - d is the damping factor (a float between 0 and 1, e.g., 0.85)
     - N is the total number of pages in the graph
     - S is the sum, over all pages that link to the current page, of
       (CurrentRank(page_j) / numLinks(page_j))
   
   Input:
     - pr: current PageRank map (string -> float)
     - d: damping factor (float)
     - graph: list of (string * string) representing the graph's links
   Output:
     - updated PageRank map (string -> float) after one iteration
       of the algorithm
*)
let stepPageRank pr d graph =
    (* raise (Failure "TODO: implement stepPageRank") *)
    let n = numPages graph in (* Using the previously implemented numPages to get the unique number of pages in the graph *)
    PageRank.fold (fun page _ new_pr ->
      let back_links = getBacklinks graph page in (*Using the previously implemented getBacklinks to get the set of backlinks*)
      let s =   (*Calculate the contribution of each backlink*)
        PageSet.fold (fun back_link acc ->
          let current_rank = PageRank.find back_link pr in  (*Extract the current rank from the map*)
          let outbound_links = numLinks graph back_link in  (*Get the number of outbound links*)
          if outbound_links > 0 then acc +. (current_rank /. float_of_int outbound_links) (*if a back_link has any outbound links, then add its contribution to the acc*)
          else acc
        ) back_links 0.0
      in
      let new_rank = ((1.0 -. d) /. float_of_int n) +. (d *. s) in  (*Calculate the new rank for the page with the formula. S is given by the block above which gives us the contributions from back_links*)
      PageRank.add page new_rank new_pr (*Add the new rank to the map*)
    ) pr PageRank.empty


(*
   iterPageRank: Iterates the PageRank algorithm until convergence.
   The function repeatedly applies the stepPageRank function until
   the largest change in any page's rank is less than the specified
   delta.
   
   Input:
     - pr: initial PageRank map (string -> float)
     - d: damping factor (float)
     - graph: list of (string * string) representing the graph's links
     - delta: a threshold (float) such that iteration stops when the
       maximum change is less than delta
   Output:
     - a converged PageRank map (string -> float) where the maximum
       rank change is below delta
*)

(* Helper function to calculate the difference between rank values of two rank maps*)
let change pageRank1 pageRank2 =
  PageRank.fold (fun page rank1 acc ->  (*Iterate over both pages and extract the current rank value from PageRank1 and the updated rank value from PageRank2*)
    let rank2 = PageRank.find page pageRank2 in
    let diff = abs_float (rank1 -. rank2) in
    if diff > acc then diff else acc  (* acc keeps track of the difference, if the difference is > than the difference in acc, then acc get's updated to the new differece*)
  ) pageRank1 0.0

let iterPageRank pr d graph delta =
    (* raise (Failure "TODO: implement iterPageRank") *)
    let rec iterate current_rank =  (*Function to iterate till the difference falls below the given threshold delta*)
      let new_rank = stepPageRank current_rank d graph in (* Using the previously implemented stepPageRanks to calculate the new rank based on the current rank and the giaven damping factor*)
      let diff = change current_rank new_rank in  (*Compute the difference between the updated rankd and the current rank using the change fucntion*)
      if diff < delta then new_rank (*Iteration continues till the difference is less than the given delta, aka the algorithm has converged and the new rank is given*)
      else iterate new_rank
    in
    iterate pr (*Call the iterate function, it starts with the initial given rank map*)


(*
   rankPages: Produces a ranked list of pages from the PageRank map.
   The list is sorted in ascending order based on each page's
   PageRank value (from least popular to most popular).
   It is assumed that no two pages have the same rank.
   
   Input: pr: PageRank map (string -> float)
   Output: a list of pages (strings) sorted in ascending order by
   their rank values
*)
let rankPages pr =
    (* raise (Failure "TODO: implement rankPages") *)
    let pr_list = PageRank.bindings pr in  (*Convert map into a list of tuples for sorting*)
    let sorted_pr_list = List.sort (fun (_, rank1) (_, rank2) -> compare rank1 rank2) pr_list in (*Using the sort function to compare the second element of each tuple (the rank) to sort in ascending order*)
    List.map (fun (page, _) -> page) sorted_pr_list (*Extract just he first elemnts from the tuples (the pages), giving just the list of pages sorted in ascending order*)
