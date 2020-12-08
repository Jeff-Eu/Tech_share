
* To list remote branches:\
`git branch -r`\
You can check them out as local branches with:\
`git checkout -b LocalName origin/remotebranchname`\
[-- Ref](https://stackoverflow.com/a/10313379/1613961)

* 一般git指令
	* `git status`
	* `git commit -a`   // 將unstaged也全部 commit，建議先用 git status 看狀態
* vi 模式下指令:
	* `:x`
	* Reference: http://www.lagmonster.org/docs/vi.html

* 回到merge/rebase之前的狀態
	*  git reset ORIG_HEAD\
	from [Youtuber](https://www.youtube.com/watch?v=HeF7dwVyzow&feature=player_embedded)

* 如下圖 How to effectively merge a range of commits on branch-test (F) upon the top of branch-master?

	![merge range](\imgs\merge_range.jpg)

如果想將test的range of commits (F) 合併到 master 的最上面，因為master在合併進test後有再修改過，若直接在master上使用 cherry pick from (F)，可能會導致要處理多次conflicts的情形(每筆commit的cherry pick可能會各別遇到conflict)，如果只想處理一次conflict，該怎麼做？

Ans: 從master merge到test前的commit建立一個 branch-Fix，將(F)的range commits用range cherry pick到branch-Fix中，最後再將branch-Fix合併到branch-master，就最多只要處理conflict一次。