import os
my_secret = os.environ['Token']
import discord
from discord.ext import commands,tasks
from discord.ext.commands import Bot,has_permissions
from webserver import keep_alive
from replit import db
import datetime
from dateutil.tz import gettz



bot = commands.Bot(command_prefix='!')
client = discord.Client()

current = datetime.datetime.now()
db['all_contests'] = []

@bot.event
async def on_ready():
  print('Bot is ready')

@bot.command()
async def info(ctx):
  await ctx.channel.send(f'Your Name :{ctx.author.name}')

@bot.command()
async def set(ctx, platform, cpid):
  await ctx.channel.send(f'{platform} profile for {ctx.author.name} has been set to {cpid} ')
  
@bot.command(pass_context=True)
@has_permissions(administrator=True)
async def add(ctx,platform,day,month,hour,minutes,link,*,contest):
	if platform.upper()=='CODEFORCES' or platform.upper()=='CODECHEF' or platform.upper()=='ATCODER':
		db[contest]={}
		temp=db[contest]
		temp['platform']=platform.upper()
		temp['contest']=contest
		temp['day']=day
		temp['month']=month
		temp['hour']=hour
		temp['minutes']=minutes
		temp['link']=link
		db[contest]=temp
		db['all_contests'].append(contest)
		await ctx.channel.send(f'Contest added: \n {contest} on {platform} wil be held on {day}/{month} at time {hour}/{minutes} \n Link: {link}')


@bot.command(pass_context=True)
@has_permissions(administrator=True)
async def clear_contests(ctx):
	for contests in db['all_contests']:
		contest = contests
		db['all_contests'].pop()
		del db[contests]
		await ctx.channel.send(f' {contest} \n Contest has been deleted by the owner')
	
	

@bot.command()
async def contests(ctx):
  for contests in db['all_contests']:
  	contests_list = discord.Embed(title="Contest",color=0x2ecc71)
  	contests_list.add_field(name="Platform",value=db[contests]['platform'])
  	contests_list.add_field(name="Contest Name",value=db[contests]['contest'])
  	contests_list.add_field(name="Link",value=db[contests]['link'])
  	contests_list.add_field(name="Date",value=( db[contests]['day'] + "/" + db[contests]['month'] ) )
  	contests_list.add_field(name="Time",value=( db[contests]['hour'] + ":" + db[contests]['minutes'] ) )
  	await ctx.channel.send(embed=contests_list)
  	  	

@tasks.loop(hours=1)
async def contest_loop():
	await bot.wait_until_ready()
	channel = bot.get_channel(896310809888714772)
	await channel.send('This loop is executed')
	current = datetime.datetime.now(tz=gettz('Asia/Kolkata'))
	cday = current.day
	cmonth = current.month
	chour = current.hour
	cminutes = current.minute
	for contests in db['all_contests']:
		if(cday==contests['day'] and cmonth==contests['month'] and (chour==(contests['hour']-1) or chour==contests['hour'] ) ):
			clist = discord.Embed(title="Upcoming Contest Alert",color=0x992d22)
			clist.add_field(name="Platform",value=db[contests]['platform'])
			clist.add_field(name="Contest Name",value=db[contests]['contest'])
			clist.add_field(name="Link",value=db[contests]['link'])
			clist.add_field(name="Date",value=( db[contests]['day'] + "/" + db[contests]['month'] ) )
			clist.add_field(name="Time",value=( db[contests]['hour'] + ":" + db[contests]['minutes'] ) )
			clist.set_image(url="https://media.giphy.com/media/Rhr6OQDIoUOtDCcxD2/giphy.gif")
			await ctx.channel.send(embed=clist)
		elif(cday==contests['day'] and cmonth==contests['month'] and chour==(contests['hour']+1)):
			del db[contests]
			db['all_contests'].remove(contests)






@bot.command()
async def commands(ctx):
  	helpl = discord.Embed(title="Commands",color=0x95a5a6)
  	helpl.add_field(name=" ",value=" ")
  	helpl.add_field(name="!contests",value="Prints the list of all Upcoming Contests")
  	helpl.add_field(name="!info",value="Prints your own Username")
  	helpl.add_field(name="!commands",value="Specifies all the commands")
  	helpl.add_field(name="!set {Platform Name} {Handle}",value="Not in functionality currently !!!!" )
  	helpl.add_field(name="!add {Platform} {Date} {Time} {Link} {Contest}",value="Administrator Command Only")
  	await ctx.channel.send(embed=helpl)


contest_loop.start()
keep_alive()

bot.run(my_secret)
