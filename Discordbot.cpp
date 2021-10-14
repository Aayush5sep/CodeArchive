import os
my_secret = os.environ['Token']
import discord
from discord.ext import commands,tasks
from discord.ext.commands import Bot,has_permissions
from webserver import keep_alive
from replit import db
import datetime

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
  print('start executed')
  for contests in db['all_contests']:
  	print(contests)
  	contests_list = discord.Embed(title="Contest",color=0x2ecc71)
  	contests_list.add_field(name="Platform",value=db[contests]['platform'])
  	contests_list.add_field(name="Contest Name",value=db[contests]['contest'])
  	contests_list.add_field(name="Link",value=db[contests]['link'])
  	await ctx.channel.send(embed=contests_list)
  	print('for loop executed')
  print('end executed')

@tasks.loop(minutes=5)
async def contest_loop():
	await bot.wait_until_ready()
	channel = bot.get_channel(896310809888714772)
	await channel.send('Loop Executed')


keep_alive()
contest_loop.start()

bot.run(my_secret)
