#pythran export score_text(str, str:int dict)
#runas score_text("e", { "d": 1 })
import string

def score_text(txt,kwdict):

	score=0
	for kw in kwdict.keys():
		if string.find(txt,kw)>-1:
			score+=kwdict[kw]
	return score
