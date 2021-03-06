import os
import sys
import plotly as py
import pandas as pd
from gantt_functions import create_gantt

def main(argv):
	#df = pd.read_csv('test.csv')
	solutionFolder = "..\\solutions"
	solutionFile = argv[0]
	df = pd.read_csv(solutionFolder + "\\" + solutionFile + ".csv")
	# Need list of more colors, up to 20 (max number of jobs)?
	colors = ['#333F44', '#93e4c1', '#660066', '#006666', '#008877', '#801010', '#808000', '#123456', '#F44333','#1A3AF0']
	fig = create_gantt(df, colors=colors, show_colorbar=True, index_col='Job',
	                      bar_width=0.2, showgrid_x=True, showgrid_y=True, group_tasks=True)
	py.offline.plot(fig, filename=solutionFile + '.html')

if __name__ == "__main__":
	main(sys.argv[1:])