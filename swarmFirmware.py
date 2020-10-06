import argparse
import os
from multiprocessing import Pool

parser = argparse.ArgumentParser(description='Launch multiple firmwares.')
parser.add_argument("-s", "--simsendport", required=False, default=15001, help="Starting sim send port.")
parser.add_argument("-r", "--simrecvport", required=False, default=15000, help="Starting sim recv port.")

parser.add_argument("-q", "--groundsendport", required=False, default=14550, help="Starting ground send port.")
parser.add_argument("-w", "--groundrecvport", required=False, default=14551, help="Starting ground recv port.")

parser.add_argument("-d", "--drones", required=True, help="Amount of drones.")
parser.add_argument("-e", "--exec", required=False, default="cmake-build-debug/MicroDroneFirmware", help="Executable location.")

args = vars(parser.parse_args())
simPorts = (args['simsendport'], args['simrecvport'])
groundPorts = (args['groundsendport'], args['groundrecvport'])

cmds = []

for i in range(0, int(args['drones'])):
    execString = f"{args['exec']} --commsTx={groundPorts[0]} --commsRx={groundPorts[1]} --simTx={simPorts[0]} --simRx={simPorts[1]}"
    cmds.append(execString)
    groundPorts = (int(groundPorts[0]) + 2, int(groundPorts[1]) + 2)
    simPorts = (int(simPorts[0]) + 2, int(simPorts[1]) + 2)

def run_process(process):    
    #print('{}'.format(process))                                                         
    os.system(process)                                       
                                                                                
                                                                                
pool = Pool(processes=int(args['drones']))
pool.map(run_process, cmds)                                                      